#include <GL/glew.h>
#include<GL/glut.h>
#include <GLFW/glfw3.h> 
#include <stdio.h>
#include <iostream>

#include <soil.h>
#include "shader_s.h"
//----------------------------------------------------------------
float vertices[] = {
	0.5f,  0.5f,  0.0f,		1.0f,0.0f, 0.0f,		 1.0f, 1.0f,
	0.5f, -0.5f,  0.0f,		0.0f, 1.0f, 0.0f,		 1.0f, 0.0f,
	-0.5f, -0.5f,  0.0f,	0.0f, 0.0f,  1.0f,		 0.0f, 0.0f,
	-0.5f, 0.5f,  0.0f,		1.0f, 1.0f,  0.0f,		 0.0f, 1.0f,
};
unsigned int indices[] =
{
	0,1,3,
	1,2,3
};
//----------------------------------------------------------------

int main()
{
	//----------------------------------------------------------------
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);


	glewExperimental = GL_TRUE;
	glewInit();


	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);


	//----------------------------------------------------------------
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// textures
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nChannels;
	unsigned char* data = SOIL_load_image("texture1.png", &width, &height, 0, SOIL_LOAD_RGB);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else
	{
		std::cout << "texture error\n";
	}
	SOIL_free_image_data(data);


	Shader ourShader("vertexshader.vs", "fragmentshader.fs");

	//----------------------------------------------------------------

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, texture);

		ourShader.use();
		glBindVertexArray(VAO);
		glEnable(GL_DEPTH_TEST);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//----------------------------------------------------------------
	return 0;
}