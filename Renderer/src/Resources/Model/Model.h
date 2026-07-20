#pragma once
#include "Resources/Utility/Buffer.h"
#include "Resources/Utility/Shader.h"
#include "Resources/Utility/Texture.h"

#include "Resources/Shapes/Shape.h"

class Model
{
public:

	Model();


	void BindShape(Shape* shape);

	void BindBuffer(GLuint index, size_t size, size_t stride, size_t offset);

	void BindTexture(std::string path, int x, int y, int comp,
					int req_comp, GLenum textureUnit, std::string uniformName,
					GLuint index, size_t size,
					size_t stride, GLuint offset);

	void BindShader(std::string vertexPath, std::string fragPath);


	inline bool GetSucces() const { return m_Success; }
	void OnUpdate();
	void Render();
	void Draw();

private:


private:

	Shape* m_Shape = nullptr;
	Buffer* m_Buffer = nullptr;
	Shader* m_Shader = nullptr;
	Texture* m_Texture = nullptr;
	bool m_Success = false;
};

