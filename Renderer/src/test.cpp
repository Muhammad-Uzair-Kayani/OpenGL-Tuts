//Core Rendering Libraries
#include "ResourceManager/Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "ResourceManager/stb_image.h"
// Include the GLAD and GLFW headers for OpenGL functionality.
#include <GLFW\glfw3.h>

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
float vertices[] =
{
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Bottom left
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom right
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f, // Top middle
	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Top left
	 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f  // Top Right
};

unsigned int indices[] =
{
	0, 1, 3,
	3, 1, 4// Square
};

GLuint VBO, VAO, EBO;
GLuint texture0, texture1;
int t_Width, t_Height, nrChannels;
std::unique_ptr<Shader> shader;

//fUNCTION DEFINITIONS
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

	//Once we initialized the GLAD now we,
	// tell opengl from where to where you have ability to render.
	// In this case we are telling OpenGL to render from the bottom left corner of the window
	// to the top right corner of the window.
	glViewport(0, 0, 800, 600);
}

void InitObjects()
{

	//Creating and Attching Textures
	//First loading the texture with correct format and then 
	//creating the texture object and binding it to the correct target.
	unsigned char* data = stbi_load("src\\ResourceManager\\Textures\\wall.jpg",
										&t_Width, &t_Height, &nrChannels, 0);
	if (!data) std::cout << "Failed to load texture" << std::endl;
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &texture0);
		glBindTexture(GL_TEXTURE_2D, texture0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_Width, t_Height, 0,
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	shader = std::make_unique<Shader>(
		"src\\ResourceManager\\Shaders\\VertexShader.txt",
		"src\\ResourceManager\\Shaders\\FragmentShader.txt");
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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// Bind the shader program and vertex array object (VAO) for rendering.;
	glBindVertexArray(VAO);
	shader->Use(texture0, texture1);

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
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

int main()
{

	InitWIN();
	
	InitObjects();

	//Main loop
	Run();

	CleanUp();
}