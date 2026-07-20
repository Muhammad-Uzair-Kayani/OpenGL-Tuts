#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Resources/Utility/Buffer.h"
#include "Resources/Utility/Shader.h"
#include "Resources/Utility/Texture.h"

#include "Resources/Shapes/Shape.h"

class Model
{
public:

	Model();


	void BindShape(Shape* shape, bool is3D = false);

	void BindBuffer(GLuint index, size_t size, size_t stride, size_t offset, std::string mat4Name = "");

	void BindTexture(std::string path, int x, int y, int comp,
					int req_comp, GLenum textureUnit, std::string uniformName,
					GLuint index, GLuint size,
					size_t stride, GLuint offset);

	void BindShader(std::string vertexPath, std::string fragPath);


	inline bool GetSucces() const { return m_Success; }
	void OnUpdate();
	void Render();
	void Draw();

	void SetPosition(float x, float y, float z, std::string mat4Name);

private:

	void BindBufferP(GLuint index, size_t size, size_t stride, size_t offset);

private:

	Shape* m_Shape = nullptr;
	Buffer* m_Buffer = nullptr;
	Shader* m_Shader = nullptr;
	Texture* m_Texture = nullptr;
	bool m_Success = false;
	bool m_Shape3D = false;
	glm::vec3 m_ModelPosition;
	glm::mat4 m_ModelMatrix;
};

