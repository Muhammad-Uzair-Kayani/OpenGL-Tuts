#pragma once
#include <string>
#include <glad/glad.h>
#include <unordered_map>

class Texture
{
public:

	Texture(std::string path, int x, int y, int comp,
		int req_comp, GLenum textureUnit, GLuint uniformLoc,
		GLuint index, size_t size,
		size_t stride, GLuint offset);

	void Bind();
	void Update();
	void Draw();
	void Render();


private:

	unsigned char* LoadImage(std::string path, int& x, int& y,
								int& comp, int req_comp);

	void Init(std::string path, int x, int y, int comp, int req_comp, GLenum textureUnit, GLuint unifromLoc,
		GLuint index, size_t size,
		size_t stride, GLuint offset);

private:
	GLuint m_TextureID;
};

