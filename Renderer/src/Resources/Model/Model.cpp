#include "Model.h"
#include <string>

Model::Model()
{

}

void Model::BindShape(Shape* shape)
{
	if (!m_Shader)
	{
		std::cout << "ERROR CREATE THE PROGRAM FIRST\n";
		return;
	}
	m_Shape = shape;
}

void Model::BindBuffer(GLuint index, size_t size, size_t stride, size_t offset)
{
	if (!m_Shape)
	{
		std::cout << "ERROR BIND THE SHAPE FIRST\n";
		return;
	}
	m_Buffer = new Buffer(m_Shape->GetSize(), m_Shape->GetVertices(), index, size, stride, offset);
	m_Success = true;
}

void Model::BindTexture(std::string path, int x, int y, int comp, 
						int req_comp, GLenum textureUnit, std::string uniformName,
						GLuint index, size_t size,
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

