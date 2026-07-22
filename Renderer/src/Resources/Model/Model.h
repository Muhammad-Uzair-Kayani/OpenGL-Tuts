#pragma once
#include <functional>
#include <tuple>
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

	Model(Shape* shape, glm::vec3 position, std::string name,
		std::function<std::vector<std::tuple<float, float, float>>()>);

	void BindBuffer(GLuint index, size_t size,
					size_t stride, size_t offset);

	void BindTexture(std::string path, int x, int y, int comp,
					int req_comp, GLenum textureUnit, std::string uniformName,
					GLuint index, GLuint size,
					size_t stride, GLuint offset);

	void BindShader(std::string vertexPath, std::string fragPath);

	void TransformObject(glm::mat4 projection, glm::mat4 view);

	inline bool GetSucces() const { return m_Success; }
	void OnUpdate(glm::mat4 projection, glm::mat4 view);
	void Render();
	void Draw();

	void SetPosition();


public:

	std::function<std::vector<std::tuple<float, float, float>>()> m_CallBack;

private:


private:

	Shape* m_Shape = nullptr;
	Buffer* m_Buffer = nullptr;
	Shader* m_Shader = nullptr;
	Texture* m_Texture = nullptr;

	bool m_Success = false;

	std::string m_Uniform;
	glm::vec3 m_ModelPosition;
	glm::vec3 m_Rotation;
	glm::mat4 m_ModelMatrix;
};

