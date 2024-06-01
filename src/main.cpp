#include <iostream>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "shader.h"
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
	if (!glfwInit()) {
        return -1;
    }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Quill Viewer", NULL, NULL);
	if (window == NULL)
	{
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

	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader shader;
	GLuint vertexshader, fragmentshader, shaderprogram;
    vertexshader = shader.init_shaders(GL_VERTEX_SHADER, "../res/shaders/vertex.glsl") ;
    fragmentshader = shader.init_shaders(GL_FRAGMENT_SHADER, "../res/shaders/fragment.glsl") ;
    shaderprogram = shader.init_program(vertexshader, fragmentshader) ;

	// works up to here

	float vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 0.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VBO, EBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// 设置环绕和过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("../resourcepacks/test/textures/oak_leaves.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// 设置环绕和过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 加载图片
	data = stbi_load("../resourcepacks/test/textures/oak_log.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	glUniform1i(glGetUniformLocation(shaderprogram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderprogram, "texture2"), 1);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(25.0 / 255.0, 25.0 / 255.0, 25.0 / 255.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderprogram);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
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