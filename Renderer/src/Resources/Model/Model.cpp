#include "Model.h"
#include <string>

Model::Model() : m_ModelPosition(0.0f, 0.0f, 0.0f), m_ModelMatrix(1.0f)
{
	
}

void Model::BindShape(Shape* shape, bool is3D)
{
	if (!m_Shader)
	{
		std::cout << "ERROR CREATE THE PROGRAM FIRST\n";
		return;
	}
	m_Shape = shape;
	m_Shape3D = is3D;
}

void Model::BindBufferP(GLuint index, size_t size, size_t stride, size_t offset)
{
	if (!m_Shape)
	{
		std::cout << "ERROR BIND THE SHAPE FIRST\n";
		return;
	}
	m_Buffer = new Buffer(m_Shape->GetSize(), m_Shape->GetVertices(), index, size, stride, offset);
	m_Success = true;

}

void Model::BindBuffer(GLuint index, size_t size, size_t stride, size_t offset, std::string mat4Name /*= ""*/)
{
	BindBufferP(index, size, stride, offset);
	if (m_Shape3D && mat4Name != "")
		SetPosition(m_ModelPosition.x, m_ModelPosition.y, m_ModelPosition.z, mat4Name);
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
	m_Buffer->BindVertexArray();
	GLuint uniformLoc = m_Shader->GetTextureID(uniformName);
	m_Texture = new Texture(path, x, y, comp, req_comp, textureUnit, uniformLoc, index, size, stride, offset);
}

void Model::BindShader(std::string vertexPath, std::string fragPath)
{
	m_Shader = new Shader(vertexPath, fragPath);
}

void Model::OnUpdate()
{
	m_Shader->UseProgram();
	m_Buffer->BindVertexArray();
}

void Model::Render()
{

}

void Model::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, m_Shape->GetVertexCount());
}


void Model::SetPosition(float x, float y, float z, std::string mat4Name)
{
	m_ModelPosition = glm::vec3(x, y, z);
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_ModelPosition);

	GLuint transLoc = glGetUniformLocation(m_Shader->GetID(), mat4Name.c_str());
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));
}

