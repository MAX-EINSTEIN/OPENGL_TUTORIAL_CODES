#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

void processInput(GLFWwindow * window);
void framebuffer_size_callback(GLFWwindow * window, int width, int height);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow * window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Practice", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error... " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error";
	}




	Shader myShader("vShader.vert", "fShader.frag");

	GLfloat vertices[] = {
		 0.0f,  1.0f, 0.0f,		1.0f, 0.0f, 0.0f, // top center   (0)
		-0.5f,  0.0f, 0.0f,		0.0f, 1.0f, 0.0f, // middle left  (1)
		 0.5f, -0.0f, 0.0f,		0.0f, 0.0f, 1.0f, // middle right (2)
		-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f, // bottom left  (3)
		 0.0f, -1.0f, 0.0f,     0.0f, 0.0f, 1.0f, // bottom middle(4)
		 1.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f  // bottom right (5)
	};

	GLuint indices[] = {
		0,1,2,
		3,1,4,
		4,2,5
	};

	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		myShader.use();

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);






	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}