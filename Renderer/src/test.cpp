//Core Rendering Libraries
#include "ResourceManager/Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "ResourceManager/stb_image.h"
// Include the GLAD and GLFW headers for OpenGL functionality.
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//C++ Standard Libraries
#include <memory>

//Some global Data to deal with in different functions
GLFWwindow* window;
unsigned int width = 800;
unsigned int height = 600;
const char* title = "OpenGL Window";

double mousePosX = 0.0f;
double mousePosY = 0.0f;

float Xcor = 0.0f;
float Ycor = 0.0f;
float lastXcor = 0.0f;
float lastYcor = 0.0f;
float deltaXcor = 0.0f;
float deltaYcor = 0.0f;

bool posRecorded = false;

//dATA dEFINITIONS
//Vertices
float vertices[] = {
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

unsigned int indices[] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)
};

GLuint VBO, VAO, EBO;
GLuint texture0, texture1;
int t_Width, t_Height, nrChannels;
std::unique_ptr<Shader> shader;

//fUNCTION DEFINITIONS

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glm::mat4 perspective;
	perspective = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);
	GLuint viewLoc = glGetUniformLocation(shader->GetID(), "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(perspective));
}

void InitWIN()
{
	// Initialize the GLFW library.
	glfwInit();

	// Tell GLFW which version of OpenGL context we want to create.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Request the Core Profile of OpenGL.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window and an associated OpenGL context.
	window = glfwCreateWindow(width, height, title, NULL, NULL);

	// Safety check.
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	// Make this window's OpenGL context the current context on this thread.
	// All subsequent OpenGL calls will affect this context and render to this window.
	glfwMakeContextCurrent(window);

	//Initialize GLAD to load OpenGL function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	//Once we initialized the GLAD now we,
	// tell opengl from where to where you have ability to render.
	// In this case we are telling OpenGL to render from the bottom left corner of the window
	// to the top right corner of the window.
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
}

void InitObjects()
{

	//Creating and Attching Textures
	//First loading the texture with correct format and then 
	//creating the texture object and binding it to the correct target.
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("src\\ResourceManager\\Textures\\wall.jpg",
										&t_Width, &t_Height, &nrChannels, 0);
	if (!data) std::cout << "Failed to load texture" << std::endl;
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &texture0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, texture0);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_Width, t_Height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}

	data = stbi_load("src\\ResourceManager\\Textures\\face.png",
		&t_Width, &t_Height, &nrChannels, 0);
	if (!data) std::cout << "Failed to load texture" << std::endl;
	else
	{
		glActiveTexture(GL_TEXTURE1);
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t_Width, t_Height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}

	//Creating Buffer & Array Objects& Attributes & Shaders
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	shader = std::make_unique<Shader>(
		"src\\ResourceManager\\Shaders\\VertexShader.txt",
		"src\\ResourceManager\\Shaders\\FragmentShader.txt");

	shader->Use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f),
		glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 perspective;
	perspective = glm::perspective(glm::radians(45.0f), (800.0f / 600.0f), 0.1f, 100.0f);


	GLuint transLoc = glGetUniformLocation(shader->GetID(), "model");
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(model));

	GLuint viewLoc = glGetUniformLocation(shader->GetID(), "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(perspective));

	GLuint projectionLoc = glGetUniformLocation(shader->GetID(), "view");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(view));


	GLuint texture0Loc = glGetUniformLocation(shader->GetID(), "texture1");
	glUniform1i(texture0Loc, 0);
	GLuint texture1Loc = glGetUniformLocation(shader->GetID(), "texture2");
	glUniform1i(texture1Loc, 1);
}


void ProcessInput()
{
	// Check if the user has pressed the escape key.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		// If the escape key is pressed, set the window to close.
		glfwSetWindowShouldClose(window, true);
	}

}

void UpdateMousePosition()
{
	// Get the current mouse position in window coordinates.
	glfwGetCursorPos(window, &mousePosX, &mousePosY);
	
	Xcor = (mousePosX / width) * 2.0f - 1.0f; // Normalize to [-1, 1]
	Ycor = 1.0f - (mousePosY / height) * 2.0f; // Normalize to [-1, 1] and invert Y-axis

	deltaXcor = Xcor - lastXcor;
	deltaYcor = Ycor - lastYcor;

	lastXcor = Xcor;
	lastYcor = Ycor;
}

void RecordPos()
{
	if (posRecorded) return;

	if ((Xcor <= 0.01f && Xcor >= -0.01f) && (Ycor <= 0.01f && Ycor >= -0.01f))
	{
		posRecorded = true;
		Xcor = 0.0f;
		Ycor = 0.0f;
		return;
	}
	
}

void UpdateTriPos()
{
	if (!posRecorded) return;

	vertices[0] += deltaXcor;
	vertices[1] += deltaYcor;
	vertices[6] += deltaXcor;
	vertices[7] += deltaYcor;
	vertices[12] += deltaXcor;
	vertices[13] += deltaYcor;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	
}

void UpdateObjectState()
{
	// Clear the color buffer to prepare for rendering.
	// 
	// Bind the shader program and vertex array object (VAO) for rendering.;
	glBindVertexArray(VAO);
	shader->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
}

void Update()
{
	// Update the state of the application, handle input, etc.
	ProcessInput();
	
	// Update the state of the objects in the scene, such as position, rotation, etc.
	UpdateMousePosition();
	RecordPos();
	UpdateTriPos();
	// Update the state of the objects in the scene,
	// such as position, rotation, etc.
	UpdateObjectState();
}

void Render()
{
	// Draw the elements (triangles) using the index buffer (EBO).
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (size_t i = 0; i < 10; ++i)
	{
		glm::mat4 _matrix = glm::mat4(1.0f);
		_matrix = glm::translate(_matrix, cubePositions[i]);

		_matrix = glm::rotate(_matrix, glm::radians(50.0f * (i + 1)) * (float)glfwGetTime(),
			glm::vec3(1, 1, 1));

		GLuint transLoc = glGetUniformLocation(shader->GetID(), "model");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(_matrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void Run()
{
	while (!glfwWindowShouldClose(window))
	{

		//pre rendering operations, updating the state of the application, etc.
		Update();
		
		//Rendering operations, drawing the scene, etc.
		Render();

		//post rendering operations, we need to swap the front and back buffers.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up and exit.
	glfwTerminate();
}

void CleanUp()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Math()
{
	glm::vec4 _vector(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 transformation = glm::mat4(1.0f);

	transformation = glm::translate(transformation, glm::vec3(1.0f, 1.0f, 0.0f));

	_vector = transformation * _vector;
	std::cout << _vector.x << ", " << _vector.y << ", " << _vector.z;

}

int main()
{

	Math();


	InitWIN();
	
	InitObjects();

	//Main loop
	Run();

	CleanUp();
}