#include "Texture.h"
#include <iostream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <Resources/Utility/stb_image.h>

Texture::Texture(std::string path, int x, int y, int comp,
				 int req_comp, GLenum textureUnit, GLuint uniformLoc,
				GLuint index, size_t size,
				size_t stride, GLuint offset)
{
	Init(path, x, y, comp, req_comp, textureUnit, uniformLoc, index, size, stride, offset);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Init(std::string path, int x, int y, int comp, int req_comp,  GLenum textureUnit, GLuint uniformLoc,
					GLuint index, size_t size,
					size_t stride, GLuint offset)
{
	unsigned char* data = LoadImage(path, x, y, comp, req_comp);
	if (!data)
	{
		std::cout << "FAILED TO LOAD TEXTURES\n";
		return;
	}

	glGenTextures(1, &m_TextureID);
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	int unit = textureUnit - GL_TEXTURE0;
	glUniform1i(uniformLoc, unit);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum format = (comp == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, x, y, 0,
		format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(index);
}

void Texture::Update()
{

}

void Texture::Draw()
{
	
}

void Texture::Render()
{

}

unsigned char* Texture::LoadImage(std::string path, int& x, int& y, int& comp, int req_comp)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(path);
		return stbi_load(path.c_str(), &x, &y, &comp, req_comp);
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << path << e.what() << "\n";
		return nullptr;
	}
}
