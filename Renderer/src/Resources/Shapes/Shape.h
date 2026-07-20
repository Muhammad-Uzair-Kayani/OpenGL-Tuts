#pragma once
#include <glad/glad.h>

struct Shape
{
	virtual size_t GetSize() = 0;
	virtual float* GetVertices() = 0;
	virtual GLuint GetVertexCount() const = 0;
};

struct Cube : public Shape
{
  float vertices[180] = {
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};

  inline size_t GetSize() override { return sizeof(vertices); }
  inline float* GetVertices() override { return vertices; }

  inline GLuint PositionIndex() const { return 0; }
  inline GLuint PositionSize() const { return 3; }
  inline size_t PositionStride() const { return 5 * sizeof(float); }
  inline size_t PositionOffset() const { return 0; }

  inline GLuint TexCoordIndex() const { return 1; }
  inline GLuint TexCoordSize() const { return 2; }
  inline size_t TexCoordStride() const { return 5 * sizeof(float); }
  inline size_t TexCoordOffset() const { return 3 * sizeof(float); }

  inline GLuint GetVertexCount() const override { return 36; }

};

struct Triangle : public Shape
{
	float vertices[15] =
	{
		// Position          // UV
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.5f, 1.0f
	};

	size_t GetSize() override
	{
		return sizeof(vertices);
	}

	float* GetVertices() override
	{
		return vertices;
	}

	GLuint GetVertexCount() const override
	{
		return 3;
	}

	// Position attribute
	inline GLuint PositionIndex() const { return 0; }
	inline GLuint PositionSize() const { return 3; }
	inline size_t PositionStride() const { return 5 * sizeof(float); }
	inline size_t PositionOffset() const { return 0; }

	// Texture attribute
	inline GLuint TexCoordIndex() const { return 1; }
	inline GLuint TexCoordSize() const { return 2; }
	inline size_t TexCoordStride() const { return 5 * sizeof(float); }
	inline size_t TexCoordOffset() const { return 3 * sizeof(float); }
};