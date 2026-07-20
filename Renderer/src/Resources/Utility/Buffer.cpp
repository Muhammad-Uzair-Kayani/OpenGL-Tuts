#include "Buffer.h"

Buffer::Buffer(size_t sizeofData, float* vertices, GLuint index, size_t size,
	size_t stride, GLuint offset)
{
	Init(sizeofData, vertices, index, size, stride, offset);
}

void Buffer::BindVertexArray()
{
	glBindVertexArray(VAO);
}

void Buffer::Init(size_t sizeofData, float* vertices, GLuint index,
					size_t size, size_t stride, size_t offset)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeofData, vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(index);

}

void Buffer::Update()
{
	//Transformations And Stuff
}