#include <iostream>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "shader.h"
#include "camera.h"
#include "element.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double x, double y);
void processKeyboardInput(GLFWwindow *window);

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

// // camera value
// glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
// glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// // delta time
// float deltaTime = 0.0f;
// float lastTime = 0.0f;

// float lastX = SCREEN_WIDTH / 2.0f;
// float lastY = SCREEN_HEIGHT / 2.0f;
float lastX;
float lastY;
float fov = 45.0f;
bool orbitMode = false;
bool translateMode = false;

Camera camera = Camera();

int main()
{	
	// Boilerplate
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // Disable top bar

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Quill Viewer", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGL(glfwGetProcAddress)) {
		std::cout << "Error Loading OpenGL" << std::endl;
		glfwTerminate();
		return -1;
	}
	// End Boilerplate

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	// glPolygonMode(GL_FRONT_FACE, GL_FILL);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	Shader shader;
	GLuint vertexshader, fragmentshader, shaderprogram;
	vertexshader = shader.init_shaders(GL_VERTEX_SHADER, "../res/shaders/vertex.glsl") ;
	fragmentshader = shader.init_shaders(GL_FRAGMENT_SHADER, "../res/shaders/fragment.glsl") ;
	shaderprogram = shader.init_program(vertexshader, fragmentshader) ;

	// works up to here

	Element testCube = Element();
	testCube._testTextures();

	// float vertices[] = {
	// 	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // 0
	// 	-0.5f, -0.5f, 0.5f, 0.0, 1.0f, // 2
	// 	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, // 1
	// 	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f // 3
	// };

	// unsigned int indices[] = {
	// 	0, 1, 2,    0, 3, 1
	// };

	// unsigned int VBO, EBO, VAO;
	// glGenVertexArrays(1, &VAO);
	// glGenBuffers(1, &VBO);
	// glGenBuffers(1, &EBO);

	// glBindVertexArray(VAO);

	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	// glEnableVertexAttribArray(0);

	// // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	// // glEnableVertexAttribArray(1);

	// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);

	// glBindVertexArray(0);

	// unsigned int texture;
	// glGenTextures(1, &texture);
	// glBindTexture(GL_TEXTURE_2D, texture);
	// // set the texture wrapping/filtering options (on the currently bound texture object)
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// // load and generate the texture
	// int width, height, nrChannels;
	// unsigned char *data = stbi_load("../resourcepacks/test/minecraft/textures/block/oak_leaves.png", &width, &height, &nrChannels, 0);
	// if (data) {
	// 	unsigned int nColors = nrChannels-3 ? GL_RGBA : GL_RGB;
	// 	// std::cout << nColors << " " << nrChannels << std::endl;
	// 	glTexImage2D(GL_TEXTURE_2D, 0, nColors, width, height, 0, nColors, GL_UNSIGNED_BYTE, data);
	// 	glGenerateMipmap(GL_TEXTURE_2D);
	// } else {
	// 	std::cout << "Failed to load texture" << std::endl;
	// }
	// stbi_image_free(data);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	while (!glfwWindowShouldClose(window))
	{	
		processKeyboardInput(window);

		// float currentFrame = glfwGetTime();
		// deltaTime = currentFrame - lastTime;
		// lastTime = currentFrame;

		glClearColor(25.0 / 255.0, 25.0 / 255.0, 25.0 / 255.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderprogram);

		// // glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, texture);

		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 model = glm::mat4(1.0f);

		glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram,"model"), 1, GL_FALSE, glm::value_ptr(model));

		testCube.draw();
		// glBindVertexArray(VAO);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// testCube.~Element(); // Don't need to call manually
	// glDeleteVertexArrays(1, &VAO);
	// glDeleteBuffers(1, &VBO);
	// glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

void processKeyboardInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
	glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
  {
	camera.mCentre = glm::vec3(0.0f, 0.0f, 0.0f);
  }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	// double xpos, ypos;
	// glfwGetCursorPos(window, &xpos, &ypos);

	// float xoffset = xpos - lastX;
	// float yoffset = lastY - ypos;
	float xoffset = lastX - xpos;
	float yoffset = ypos - lastY;

	lastX = xpos;
	lastY = ypos;

	if (orbitMode) 
		camera.orbitCam(xoffset, yoffset);
	if (translateMode)
		camera.translateCam(xoffset, yoffset);
}
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
  	if (action == GLFW_PRESS) {
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			orbitMode = true;
			return;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			translateMode = true;
			return;
		case GLFW_MOUSE_BUTTON_RIGHT:
			return;
		}
	}
	if (action == GLFW_RELEASE) {
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			orbitMode = false;
			return;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			translateMode = false;
			return;
		case GLFW_MOUSE_BUTTON_RIGHT:
			return;
		}
	}
}

// void cursor_position_callback(GLFWwindow *window, double x, double y)
// {
// 	float xpos = float((x - SCREEN_WIDTH / 2) / SCREEN_WIDTH) * 2;
// 	float ypos = float(0 - (y - SCREEN_HEIGHT / 2) / SCREEN_HEIGHT) * 2;

// 	// cout << "xpos " << xpos << endl;
// 	// cout << "ypos " << ypos << endl;
// 	return;
// }

void scroll_callback(GLFWwindow *window, double x, double y)
{
	camera.zoomCam((float)y);
	return;
}

// #include <iostream>
// #include <cmath>

// double left, right, top, bottom;
// double xmin, xmax, ymin, ymax;
// float scale = 1.0f;

// void drawGrid()
// {
//   // glColor3f(0.5f, 0.5f, 0.5f);
//   // glBegin(GL_LINES);
//   // for (float x = -1.0f; x <= 1.0f; x += 0.1f)
//   // {
//   //   glVertex2f(x, -1.0f);
//   //   glVertex2f(x, 1.0f);
//   // }
//   // for (float y = -1.0f; y <= 1.0f; y += 0.1f)
//   // {
//   //   glVertex2f(-1.0f, y);
//   //   glVertex2f(1.0f, y);
//   // }
//   // glEnd();
//   glBegin(GL_LINES);
//   for (int i = 0; i <= 10; i++)
//   {
//     glVertex2f(left + i * (right - left) / 10, bottom);
//     glVertex2f(left + i * (right - left) / 10, top);

//     glVertex2f(left, bottom + i * (top - bottom) / 10);
//     glVertex2f(right, bottom + i * (top - bottom) / 10);
//   }
//   glEnd();
// }

// void drawAxis()
// {
//   glBegin(GL_LINES);
//   glVertex2f(left, 0);
//   glVertex2f(right, 0);

//   glVertex2f(0, top);
//   glVertex2f(0, bottom);
//   glEnd();
// }

// double func(double x)
// {
//   return sin(x);
// }

// void draw(GLFWwindow *window)
// {
//   glClear(GL_COLOR_BUFFER_BIT);

//   // int width, height;
//   // glfwGetFramebufferSize(window, &width, &height);
//   // glViewport(0, 0, width, height);
//   // glClear(GL_COLOR_BUFFER_BIT);

//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   glOrtho(-1.0f * scale, 1.0f * scale, -1.0f * scale, 1.0f * scale, -1.0f, 1.0f);
//   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity();

//   glColor3f(0.5f, 0.5f, 0.5f);
//   drawGrid();

//   glColor3f(0.5f, 0.5f, 0.5f);
//   drawAxis();

//   glColor3f(0, 0, 1);
//   glBegin(GL_LINE_STRIP);
//   for (int i = 0; i < 1000; i++)
//   {
//     double x = left + i * (right - left) / 1000;
//     double y = func(x);
//     glVertex2f(x, y);
//   };
//   glEnd();

//   glFlush();

//   // drawGrid();

//   glfwSwapBuffers(window);
// }

// void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
// {
//   scale += yoffset * -0.1f;
// }

// int main()
// {
//   if (!glfwInit())
//   {
//     std::cout << "Failed to initialize GLFW\n";
//     return -1;
//   }

//   GLFWwindow *window = glfwCreateWindow(800, 600, "Graphing Program Test", NULL, NULL);
//   glfwSetWindowPos(window, 100, 100);
//   if (!window)
//   {
//     std::cout << "Failed to open GLFW window\n";
//     glfwTerminate();
//     return -1;
//   }

//   glfwMakeContextCurrent(window);
//   glewExperimental = GL_TRUE;
//   if (!gladLoadGL(glfwGetProcAddress))
//   {
//     std::cout << "Failed to initialize GLAD\n";
//     return -1;
//   }

//   left = -10;
//   right = 10;
//   bottom = -10;
//   top = 10;

//   xmin = left;
//   xmax = right;
//   ymin = bottom;
//   ymax = top;

//   glfwSetScrollCallback(window, scroll_callback);

//   while (!glfwWindowShouldClose(window))
//   {
//     draw(window);
//     glfwPollEvents();
//   }

//   glfwTerminate();
//   return 0;
// }