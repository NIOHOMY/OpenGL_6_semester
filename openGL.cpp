
#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include<GL/glut.h>
#include <GLFW/glfw3.h> 
#include <stdio.h>
#include <iostream>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/transform.hpp>


#include <soil.h>
#include "shader_s.h"


static const GLfloat g_vertex_buffer_data[] = {
			-0.5f,-0.5f,-0.5f, // Треугольник 1 : начало
			-0.5f,-0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f, // Треугольник 1 : конец
			 0.5f, 0.5f,-0.5f, // Треугольник 2 : начало
			-0.5f,-0.5f,-0.5f,
			-0.5f, 0.5f,-0.5f, // Треугольник 2 : конец
			 0.5f,-0.5f, 0.5f,
			-0.5f,-0.5f,-0.5f,
			 0.5,-0.5f,-0.5f,
			 0.5f, 0.5f,-0.5f,
			 0.5f,-0.5f,-0.5f,
			-0.5f,-0.5f,-0.5f,
			-0.5f,-0.5f,-0.5f,
			-0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f,-0.5f,
			 0.5f,-0.5f, 0.5f,
			-0.5f,-0.5f, 0.5f,
			-0.5f,-0.5f,-0.5f,
			-0.5f, 0.5f, 0.5f,
			-0.5f,-0.5f, 0.5f,
			 0.5f,-0.5f, 0.5f,
			 0.5f, 0.5f, 0.5f,
			 0.5f,-0.5f,-0.5f,
			 0.5f, 0.5f,-0.5f,
			 0.5f,-0.5f,-0.5f,
			 0.5f, 0.5f, 0.5f,
			 0.5f,-0.5f, 0.5f,
			 0.5f, 0.5f, 0.5f,
			 0.5f, 0.5f,-0.5f,
			-0.5f, 0.5f,-0.5f,
			 0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f,-0.5f,
			-0.5f, 0.5f, 0.5f,
			 0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
			 0.5f,-0.5f, 0.5f
};

// Цвета для каждой вершины
static const GLfloat g_color_buffer_data[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};
//----------------------------------------------------------------

int main()
{
	//----------------------------------------------------------------
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello texture", NULL, NULL);
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

	//=================================================================
	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	//=================================================================
	//----------------------------------------------------------------

	/*
	// textures
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nChannels;
	unsigned char* data = SOIL_load_image("rainbow_texture.png", &width, &height, 0, SOIL_LOAD_RGB);

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
	*/


	Shader ourShader("vertexshader.vs", "fragmentshader.fs");

	//----------------------------------------------------------------

	while (!glfwWindowShouldClose(window)) {
        //================================================================
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(
			glm::vec3(4.0f, 3.0f, -3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4  model(1.0f);

		glm::mat4 mvp = projection * view * model;

		GLuint mvpLoc = glGetUniformLocation(ourShader.ID, "mvp");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);
        //================================================================
		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glBindTexture(GL_TEXTURE_2D, texture);


		ourShader.use();
		glBindVertexArray(vertex_array_id);
		glEnable(GL_DEPTH_TEST);
		GLuint colorLoc = glGetUniformLocation(ourShader.ID, "inputColor");

		glUniform3f(colorLoc, 1.0f, 0.0f, 0.0f); // Например, красный цвет


		glDrawArrays(GL_TRIANGLES, 0, 36);



		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//----------------------------------------------------------------
	return 0;
}