//C++ Standard Library headers for input/output,
// string manipulation, and file handling.
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <fstream>

// Include the GLAD and GLFW headers for OpenGL functionality.
#include <glad\glad.h>
#include <GLFW\glfw3.h>


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
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom left
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// Bottom right
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,//Top middle
	-0.5f,  0.5f, 0.0f, // Top left
	 0.5f,  0.5f, 0.0f  // Top Right
};

unsigned int indices[] =
{
	0,1,2, // First Triangle
};

GLuint VBO, VAO, EBO;
GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderprogram;

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

const std::string LoadFromFile(const char* path)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cout << "File not found" << std::endl;
		return "";
	}

	std::stringstream ss;
	std::string line;

	while (std::getline(file, line))
	{
		ss << line << '\n';
	}
	std::cout << ss.str();
	return ss.str();
}

void CreateShader(const char* path, GLuint& shader, GLenum type)
{
	const std::string source = LoadFromFile(path);
	const char* shaderSource = source.c_str();
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int success;
	char log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		std::cout << "FAILED TO COMPILE THE SHADER SOURCE::OPENGL MESSAGE::";
		glGetShaderInfoLog(shader, sizeof(log), NULL, log);
		std::cout << log << "\n";
		return;
	}

	std::cout << "SUCCESS IN CREATING SHADER\n";
}

void CreateShaderProgram()
{
	shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexShader);
	glAttachShader(shaderprogram, fragmentShader);
	glLinkProgram(shaderprogram);

	int success;
	char log[512];
	glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);

	if (!success)
	{
		std::cout << "FAILED TO LINK THE SHADERS::OPENGL MESSAGE::";
		glGetProgramInfoLog(shaderprogram, 512, NULL, log);
		std::cout << log << "\n";
		return;
	}

	std::cout << "SUCCESS IN CREATING SHADER PROGRAM\n";
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void InitObjects()
{
	//Creating Buffer & Array Objects& Attributes & Shaders
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Compiling Vertex& Frag Shader
	CreateShader("Resources\\VertexShader.txt", vertexShader, GL_VERTEX_SHADER);
	CreateShader("Resources\\FragmentShader.txt", fragmentShader, GL_FRAGMENT_SHADER);
	//Linking ShaderProg
	CreateShaderProgram();
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
	// Bind the shader program and vertex array object (VAO) for rendering.
	glUseProgram(shaderprogram);
	glBindVertexArray(VAO);
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
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
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
	glDeleteProgram(shaderprogram);
}

int main()
{

	InitWIN();
	
	InitObjects();

	//Main loop
	Run();

	CleanUp();
}