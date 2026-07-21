#include "Model.h"
#include <string>

Model::Model(Shape* shape, glm::vec3 pos, std::string name) 
		: m_ModelPosition(pos), m_ModelMatrix(1.0f), m_Uniform(name), m_Shape(shape)
{
	
}

void Model::BindBuffer(GLuint index, size_t size,
					   size_t stride, size_t offset)
{
	if (!m_Shader)
	{
		std::cout << "FAILED TO CREATE BUFFER OBJECT BIND SHADERS\n";
	}
	m_Buffer = new Buffer(m_Shape->GetSize(), m_Shape->GetVertices(), index, size, stride, offset);
	m_Success = true;
	m_Shader->UseProgram();
	SetPosition();
}

void Model::BindTexture(std::string path, int x, int y, int comp, 
						int req_comp, GLenum textureUnit, std::string uniformName,
						GLuint index, GLuint size,
						size_t stride, GLuint offset)
{
	if (!m_Buffer)
	{
		std::cout << "ERROR BIND THE BUFFERS FIRST\n";
		return;
	}
	m_Shader->UseProgram();
	m_Buffer->BindVertexArray();
	GLuint uniformLoc = m_Shader->GetTextureID(uniformName);
	m_Texture = new Texture(path, x, y, comp, req_comp, textureUnit, uniformLoc, index, size, stride, offset);
}

void Model::BindShader(std::string vertexPath, std::string fragPath)
{
	m_Shader = new Shader(vertexPath, fragPath);
}

void Model::TransformObject(glm::mat4 projection, glm::mat4 view)
{
	m_Shader->UseProgram();
	
	int projectionLoc = glGetUniformLocation(m_Shader->GetID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
	int viewLoc = glGetUniformLocation(m_Shader->GetID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void Model::OnUpdate(glm::mat4 projection, glm::mat4 view)
{
	m_Shader->UseProgram();
	m_Buffer->BindVertexArray();
	TransformObject(projection, view);
	Draw();
}

void Model::Render()
{

}

void Model::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, m_Shape->GetVertexCount());
}


void Model::SetPosition()
{
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_ModelPosition);
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 1.0f));

	GLuint transLoc = glGetUniformLocation(m_Shader->GetID(), m_Uniform.c_str());
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));
}

