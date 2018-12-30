#include <iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "Shader.h"

// Function : processInput()
void processInput(GLFWwindow * window);

// Function : framebuffer_size_callback()
void framebuffer_size_callback(GLFWwindow * window, int widht, int height);


// Constants : SCREEN_WIDTH AND SCREEN HEIGHT
const size_t SCREEN_WIDTH  = 800;
const size_t SCREEN_HEIGHT = 600;


// Function : Main()
int main(int argc, char * argv[])
{
	// glfw : initialise and configure
	// -------------------------------
	glfwInit();                                                         // Initialising
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// Setting Opengl ...
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						// ... Version to 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// Using Opengl Core
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// Allowing Compatibility with future versions

	// glfw : window creation
	// ----------------------
	GLFWwindow * window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Quadilateral", NULL, NULL);	// Creating a Window
	if (window == NULL)																						// Error Checking
	{
		std::cout << "\nError : GLFW Window Creation Failed !!!\n" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);																			// Activating window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);									    // getting buffer size

	// glad : load all Opengl Pointers
	// -------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))												// Loads GLAD library
	{																							            // Error Checking
		std::cout << "\nError : GLAD Initalisation Failed !!!\n" << std::endl;
		return -1;
	}




	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("vShader.vert", "fshader.frag"); 





    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
	float vertices[] = {
		 // position			// colors
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f,		0.9f, 0.9f, 0.7f // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);










	// render loop
	// -----------
	while(!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// render the triangle
		ourShader.use();
		// draw our first triangle
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // turn it on using GL_FILL
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glBindVertexArray(0); // no need to unbind it every time 



		// glfw : Swap buffers and poll IO events (keys pressed/released,mouse actions,etc.
		// --------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}





	// optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);





	// glfw : terminate, clearing all the previously allocated resources used by glfw
	// ------------------------------------------------------------------------------
	glfwTerminate();


	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow * window, int widht, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, widht, height);
}
