#pragma once
#include <glad/glad.h>

class Buffer
{
public:

	Buffer(size_t sizeofData, float* vertices, GLuint index, size_t size,
		size_t stride, GLuint offset);

	void BindVertexArray();

	void Update();
	void Draw(GLuint);
	void Render();

private:

	void Init(size_t sizeofData, float* vertices, GLuint index, size_t size, size_t stride, size_t offset);

	GLuint VBO = 0, EBO = 0, VAO = 0;

};

