#include <iostream>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "camera.h"

// int main(int, char**) {
//     GLFWwindow* window;
    
//     if (!glfwInit()) {
//         return -1;
//     }

//     window = glfwCreateWindow(640,480,"Window",glfwGetPrimaryMonitor(),NULL);
//     std::cout << "window created" << std::endl;
//     glfwMakeContextCurrent(window);
//     // glfwSetWindowPos(window, 256, 256);

//     if (!gladLoadGL(glfwGetProcAddress)) {
//         std::cout << "Error Loading OpenGL" << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     glClearColor(0.25f,0.5f,0.75f,1.0f);

//     while (glfwWindowShouldClose(window)) {
//         glfwPollEvents();

//         glClear(GL_COLOR_BUFFER_BIT);

//         glfwSwapBuffers(window);
//     }
//     glfwTerminate();
//     return 0;
// }

// #include <math.h>

// // Vertex Shader source code
// const char* vertexShaderSource = "#version 330 core\n"
// "layout (location = 0) in vec3 aPos;\n"
// "void main()\n"
// "{\n"
// "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
// "}\0";
// //Fragment Shader source code
// const char* fragmentShaderSource = "#version 330 core\n"
// "out vec4 FragColor;\n"
// "void main()\n"
// "{\n"
// "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
// "}\n\0";



// int main()
// {
// 	// Initialize GLFW
// 	glfwInit();

// 	// Tell GLFW what version of OpenGL we are using 
// 	// In this case we are using OpenGL 3.3
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// 	// Tell GLFW we are using the CORE profile
// 	// So that means we only have the modern functions
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// 	// Create a GLFWwindow object of 800 by 800 pixels
// 	GLFWwindow* window = glfwCreateWindow(800, 800, "Quill Viewer", NULL, NULL);
// 	// Error check if the window fails to create
// 	if (window == NULL)
// 	{
// 		std::cout << "Failed to create GLFW window" << std::endl;
// 		glfwTerminate();
// 		return -1;
// 	}
// 	// Introduce the window into the current context
// 	glfwMakeContextCurrent(window);

// 	//Load GLAD so it configures OpenGL
// 	gladLoadGL(glfwGetProcAddress);
// 	// Specify the viewport of OpenGL in the Window
// 	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
// 	glViewport(0, 0, 800, 800);



// 	// Create Vertex Shader Object and get its reference
// 	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
// 	// Attach Vertex Shader source to the Vertex Shader Object
// 	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
// 	// Compile the Vertex Shader into machine code
// 	glCompileShader(vertexShader);

// 	// Create Fragment Shader Object and get its reference
// 	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
// 	// Attach Fragment Shader source to the Fragment Shader Object
// 	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
// 	// Compile the Vertex Shader into machine code
// 	glCompileShader(fragmentShader);

// 	// Create Shader Program Object and get its reference
// 	GLuint shaderProgram = glCreateProgram();
// 	// Attach the Vertex and Fragment Shaders to the Shader Program
// 	glAttachShader(shaderProgram, vertexShader);
// 	glAttachShader(shaderProgram, fragmentShader);
// 	// Wrap-up/Link all the shaders together into the Shader Program
// 	glLinkProgram(shaderProgram);

// 	// Delete the now useless Vertex and Fragment Shader objects
// 	glDeleteShader(vertexShader);
// 	glDeleteShader(fragmentShader);



// 	// Vertices coordinates
// 	GLfloat vertices[] =
// 	{
// 		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
// 		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
// 		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
// 	};

// 	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
// 	GLuint VAO, VBO;

// 	// Generate the VAO and VBO with only 1 object each
// 	glGenVertexArrays(1, &VAO);
// 	glGenBuffers(1, &VBO);

// 	// Make the VAO the current Vertex Array Object by binding it
// 	glBindVertexArray(VAO);

// 	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
// 	glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 	// Introduce the vertices into the VBO
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// 	// Enable the Vertex Attribute so that OpenGL knows to use it
// 	glEnableVertexAttribArray(0);

// 	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
// 	glBindBuffer(GL_ARRAY_BUFFER, 0);
// 	glBindVertexArray(0);



// 	// Main while loop
// 	while (!glfwWindowShouldClose(window))
// 	{
// 		// Specify the color of the background
// 		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
// 		// Clean the back buffer and assign the new color to it
// 		glClear(GL_COLOR_BUFFER_BIT);
// 		// Tell OpenGL which Shader Program we want to use
// 		glUseProgram(shaderProgram);
// 		// Bind the VAO so OpenGL knows to use it
// 		glBindVertexArray(VAO);
// 		// Draw the triangle using the GL_TRIANGLES primitive
// 		glDrawArrays(GL_TRIANGLES, 0, 3);
// 		// Swap the back buffer with the front buffer
// 		glfwSwapBuffers(window);
// 		// Take care of all GLFW events
// 		glfwPollEvents();
// 	}



// 	// Delete all the objects we've created
// 	glDeleteVertexArrays(1, &VAO);
// 	glDeleteBuffers(1, &VBO);
// 	glDeleteProgram(shaderProgram);
// 	// Delete window before ending the program
// 	glfwDestroyWindow(window);
// 	// Terminate GLFW before ending the program
// 	glfwTerminate();
// 	return 0;
// }

#include <iostream>
#include <cmath>

double left, right, top, bottom;
double xmin, xmax, ymin, ymax;
float scale = 1.0f;

void drawGrid()
{
  // glColor3f(0.5f, 0.5f, 0.5f);
  // glBegin(GL_LINES);
  // for (float x = -1.0f; x <= 1.0f; x += 0.1f)
  // {
  //   glVertex2f(x, -1.0f);
  //   glVertex2f(x, 1.0f);
  // }
  // for (float y = -1.0f; y <= 1.0f; y += 0.1f)
  // {
  //   glVertex2f(-1.0f, y);
  //   glVertex2f(1.0f, y);
  // }
  // glEnd();
  glBegin(GL_LINES);
  for (int i = 0; i <= 10; i++)
  {
    glVertex2f(left + i * (right - left) / 10, bottom);
    glVertex2f(left + i * (right - left) / 10, top);

    glVertex2f(left, bottom + i * (top - bottom) / 10);
    glVertex2f(right, bottom + i * (top - bottom) / 10);
  }
  glEnd();
}

void drawAxis()
{
  glBegin(GL_LINES);
  glVertex2f(left, 0);
  glVertex2f(right, 0);

  glVertex2f(0, top);
  glVertex2f(0, bottom);
  glEnd();
}

double func(double x)
{
  return sin(x);
}

void draw(GLFWwindow *window)
{
  glClear(GL_COLOR_BUFFER_BIT);

  // int width, height;
  // glfwGetFramebufferSize(window, &width, &height);
  // glViewport(0, 0, width, height);
  // glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0f * scale, 1.0f * scale, -1.0f * scale, 1.0f * scale, -1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3f(0.5f, 0.5f, 0.5f);
  drawGrid();

  glColor3f(0.5f, 0.5f, 0.5f);
  drawAxis();

  glColor3f(0, 0, 1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < 1000; i++)
  {
    double x = left + i * (right - left) / 1000;
    double y = func(x);
    glVertex2f(x, y);
  };
  glEnd();

  glFlush();

  // drawGrid();

  glfwSwapBuffers(window);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
  scale += yoffset * -0.1f;
}

int main()
{
  if (!glfwInit())
  {
    std::cout << "Failed to initialize GLFW\n";
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(800, 600, "Graphing Program Test", NULL, NULL);
  glfwSetWindowPos(window, 100, 100);
  if (!window)
  {
    std::cout << "Failed to open GLFW window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  if (!gladLoadGL(glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  left = -10;
  right = 10;
  bottom = -10;
  top = 10;

  xmin = left;
  xmax = right;
  ymin = bottom;
  ymax = top;

  glfwSetScrollCallback(window, scroll_callback);

  while (!glfwWindowShouldClose(window))
  {
    draw(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}