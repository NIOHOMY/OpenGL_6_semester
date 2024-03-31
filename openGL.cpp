﻿

#include <iostream>

#include<GL/glew.h>
#include<gl/glew.h>
#include<glut.h>
#include <GLFW/glfw3.h>
//#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_s.h"
#include "camera.h"
#include <iostream>
#include <soil.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


// Константы
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 400;

// Камера
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 1.4f;
float lastY = SCR_HEIGHT / 1.4f;
bool firstMouse = true;

// Тайминги
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Освещение
glm::vec3 lightPos(1.2f, 1.0f, 1.4f);

int main()
{
	// glfw: инициализация и конфигурирование
//	glfwInit();
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	// glfw: создание окна
	GLFWwindow* window = glfwCreateWindow(1100, 800, "Hello Cube", nullptr, 0);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Сообщаем GLFW, чтобы он захватил наш курсор
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	// Конфигурирование глобального состояния OpenGL
	glEnable(GL_DEPTH_TEST);

	// Компилирование нашей шейдерной программы
	Shader lightingShader("basic_lighting.vs", "basic_lighting.fs");
	Shader lampShader("lamp.vs", "lamp.fs");

	// Указание вершин (и буфера(ов)) и настройка вершинных атрибутов
	float secondObjectVertices[] = {
		// Первая пирамида
		// Основание 1
		-1.4f, -1.25f, -1.4f,   1.0f, 1.0f,  0.0f,
		 1.4f, -1.25f, -1.4f,   0.0f, 1.0f,  0.0f,
		-1.4f, -1.25f,  1.4f,   1.0f, 0.0f,  0.0f,
		-1.4f, -1.25f,  1.4f,   1.0f, 1.0f,  0.0f,
		 1.4f, -1.25f,  1.4f,   1.0f, 0.0f,  0.0f,
		 1.4f, -1.25f, -1.4f,   0.0f, 0.0f,  0.0f,
		 // Основание 2
		 -1.4f, -1.75f, -1.4f,  1.0f, 1.0f,  0.0f,
		  1.4f, -1.75f, -1.4f,  0.0f, 1.0f,  0.0f,
		 -1.4f, -1.75f,  1.4f,  1.0f, 0.0f,  0.0f,
		 -1.4f, -1.75f,  1.4f,  1.0f, 1.0f,  0.0f,
		  1.4f, -1.75f,  1.4f,  1.0f, 0.0f,  0.0f,
		  1.4f, -1.75f, -1.4f,  0.0f, 0.0f,  0.0f,

		 // бок1
		-1.4f, -1.25f,  1.4f,  1.0f, 1.0f,  0.0f,
		 1.4f, -1.25f,  1.4f,  0.0f, 1.0f,  0.0f,
		-1.4f, -1.75f,  1.4f,  1.0f, 0.0f,  0.0f,
		-1.4f, -1.75f,  1.4f,  1.0f, 1.0f,  0.0f,
		 1.4f, -1.75f,  1.4f,  1.0f, 0.0f,  0.0f,
		 1.4f, -1.25f,  1.4f,  0.0f, 0.0f,  0.0f,		 
		 // бок2
		-1.4f, -1.25f,  -1.4f, 1.0f, 1.0f,  0.0f,
		 1.4f, -1.25f,  -1.4f, 0.0f, 1.0f,  0.0f,
		-1.4f, -1.75f,  -1.4f, 1.0f, 0.0f,  0.0f,
		-1.4f, -1.75f,  -1.4f, 1.0f, 1.0f,  0.0f,
		 1.4f, -1.75f,  -1.4f, 1.0f, 0.0f,  0.0f,
		 1.4f, -1.25f,  -1.4f, 0.0f, 0.0f,  0.0f,
		 // бок3
		 1.4f, -1.25f,  1.4f,   1.0f, 1.0f,  0.0f,
		 1.4f, -1.25f, -1.4f,   0.0f, 1.0f,  0.0f,
		 1.4f, -1.75f,  1.4f,   1.0f, 0.0f,  0.0f,
		 1.4f, -1.75f,  1.4f,   1.0f, 1.0f,  0.0f,
		 1.4f, -1.75f, -1.4f,   1.0f, 0.0f,  0.0f,
		 1.4f, -1.25f, -1.4f,   0.0f, 0.0f,  0.0f,
		 // бок4
		 -1.4f, -1.25f,  1.4f,  1.0f, 1.0f,  0.0f,
		 -1.4f, -1.25f, -1.4f,  0.0f, 1.0f,  0.0f,
		 -1.4f, -1.75f,  1.4f,  1.0f, 0.0f,  0.0f,
		 -1.4f, -1.75f,  1.4f,  1.0f, 1.0f,  0.0f,
		 -1.4f, -1.75f, -1.4f,  1.0f, 0.0f,  0.0f,
		 -1.4f, -1.25f, -1.4f,  0.0f, 0.0f,  0.0f,
		 // пирамида
		// Основание
		-1.0f, -3.0f, -1.0f,   1.0f, 1.0f,  0.0f,
		 1.0f, -3.0f, -1.0f,   0.0f, 1.0f,  0.0f,
		 1.0f, -3.0f,  1.0f,   1.0f, 0.0f,  0.0f,
		-1.0f, -3.0f, -1.0f,   1.0f, 1.0f,  0.0f,
		 1.0f, -3.0f,  1.0f,   1.0f, 0.0f,  0.0f,
		-1.0f, -3.0f,  1.0f,   0.0f, 0.0f,  0.0f,
		// Боковые грани
		-1.0f, -3.0f, -1.0f,  0.5f, 0.7071f, -1.7071f,
		 1.0f, -3.0f, -1.0f,   1.5f, 0.7071f, -1.7071f,
		 0.0f, -1.25f,  0.0f,   1.5f, 2.7071f, -1.7071f,
		-1.0f, -3.0f,  1.0f,  1.5f, 2.7071f,  1.7071f,
		 1.0f, -3.0f,  1.0f,   0.5f, 2.7071f,  1.7071f,
		 0.0f, -1.25f,  0.0f,   0.5f, 0.7071f,  1.7071f,
		-1.0f, -3.0f, -1.0f,  0.5f, 0.7071f, -1.7071f,
		-1.0f, -3.0f,  1.0f,  1.5f, 0.7071f,  1.7071f,
		 0.0f, -1.25f,  0.0f,  1.5f, 2.7071f, -1.7071f,
		 1.0f, -3.0f, -1.0f,   1.5f, 2.7071f, -1.7071f,
		 1.0f, -3.0f,  1.0f,   0.5f, 2.7071f,  1.7071f,
		 0.0f, -1.25f,  0.0f,   0.5f, 0.7071f,  1.7071f,

	};
	float vertices[] = {
		// Первая пирамида
		// Основание
		-0.5f, 0.5f, -0.5f,   0.5f, 1.5f,  0.5f,
		 0.5f, 0.5f, -0.5f,   0.5f, 1.5f,  0.5f,
		 0.5f, 0.5f,  0.5f,   0.5f, 1.5f,  0.5f,
		-0.5f, 0.5f, -0.5f,   0.5f, 1.5f,  0.5f,
		 0.5f, 0.5f,  0.5f,   0.5f, 1.5f,  0.5f,
		-0.5f, 0.5f,  0.5f,   0.5f, 1.5f,  0.5f,
		// Боковые грани
		-0.5f, 0.5f, -0.5f,  1.0f, 1.0f,  -1.7071f,
		 0.5f, 0.5f, -0.5f,  0.0f, 1.0f,  -1.7071f,
		 0.0f, 1.5f,  0.0f,  1.0f, 0.0f,  -1.7071f,
		-0.5f, 0.5f,  0.5f,  1.0f, 1.0f,   1.7071f,
		 0.5f, 0.5f,  0.5f,  1.0f, 0.0f,   1.7071f,
		 0.0f, 1.5f,  0.0f,  0.0f, 0.0f,   1.7071f,
		-0.5f, 0.5f, -0.5f,  1.0f, 1.0f,  -1.7071f,
		-0.5f, 0.5f,  0.5f,  0.0f, 1.0f,   1.7071f,
		 0.0f, 1.5f,  0.0f,  1.0f, 0.0f,  -1.7071f,
		 0.5f, 0.5f, -0.5f,  1.0f, 1.0f,  -1.7071f,
		 0.5f, 0.5f,  0.5f,  1.0f, 0.0f,   1.7071f,
		 0.0f, 1.5f,  0.0f,  0.0f, 0.0f,   1.7071f,
		 // Вторая пирамида
		// Основание
		-0.5f, 0.5f, -0.5f,   0.5f, -1.5f,  0.5f,
		 0.5f, 0.5f, -0.5f,   0.5f, -1.5f,  0.5f,
		 0.5f, 0.5f,  0.5f,   0.5f, -1.5f,  0.5f,
		-0.5f, 0.5f, -0.5f,   0.5f, -1.5f,  0.5f,
		 0.5f, 0.5f,  0.5f,   0.5f, -1.5f,  0.5f,
		-0.5f, 0.5f,  0.5f,   0.5f, -1.5f,  0.5f,
		// Боковые грани
		-0.5f, 0.5f, -0.5f,  1.0f, 1.0f,  -1.7071f,
		 0.5f, 0.5f, -0.5f,  0.0f, 1.0f,  -1.7071f,
		 0.0f,-0.5f,  0.0f,  1.0f, 0.0f,  -1.7071f,
		-0.5f, 0.5f,  0.5f,  1.0f, 1.0f,   1.7071f,
		 0.5f, 0.5f,  0.5f,  1.0f, 0.0f,   1.7071f,
		 0.0f,-0.5f,  0.0f,  0.0f, 0.0f,   1.7071f,
		-0.5f, 0.5f, -0.5f,  1.0f, 1.0f,  -1.7071f,
		-0.5f, 0.5f,  0.5f,  0.0f, 1.0f,   1.7071f,
		 0.0f,-0.5f,  0.0f,  1.0f, 0.0f,   1.7071f,
		 0.5f, 0.5f, -0.5f,  1.0f, 1.0f,  -1.7071f,
		 0.5f, 0.5f,  0.5f,  1.0f, 0.0f,   1.7071f,
		 0.0f, -0.5f,  0.0f, 0.0f, 0.0f,   1.7071f,
	};


	//------------------------------------------------------1----------------------------------------------------------
	// 1. Настраиваем VAO (и VBO) куба
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// Координатные атрибуты
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Атрибуты нормалей
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 2. Настраиваем VAO света (VBO остается неизменным; вершины те же и для светового объекта, который также является 3D-кубом)
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Обратите внимание, что мы обновляем шаг атрибута положения лампы, чтобы отразить обновленные данные буфера
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nChannels;
	unsigned char* data = SOIL_load_image("CrystalTexture.png", &width, &height, &nChannels, SOIL_LOAD_RGB);
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

	//--------------------------------------------------2--------------------------------------------------------------
	
	// 3. Настраиваем VAO (и VBO) второй подставки для фигуры
	unsigned int secondObjectVBO, secondObjectVAO;
	glGenVertexArrays(1, &secondObjectVAO);
	glGenBuffers(1, &secondObjectVBO);

	glBindBuffer(GL_ARRAY_BUFFER, secondObjectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondObjectVertices), secondObjectVertices, GL_STATIC_DRAW);

	glBindVertexArray(secondObjectVAO);

	// Координатные атрибуты
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Атрибуты нормалей
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture for second object
	unsigned int secondObjectTexture;
	glGenTextures(1, &secondObjectTexture);
	glBindTexture(GL_TEXTURE_2D, secondObjectTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* secondObjectData = SOIL_load_image("StandTexture.png", &width, &height, &nChannels, SOIL_LOAD_RGB);
	if (secondObjectData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, secondObjectData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Second object texture error\n";
	}
	SOIL_free_image_data(secondObjectData);
	
	//----------------------------------------------------------------------------------------------------------------

	// Цикл рендеринга
	float angle = 50.0f;
	while (!glfwWindowShouldClose(window))
	{
		// Логическая часть работы со временем для каждого кадра
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Обработка ввода
		processInput(window);

		// Рендеринг
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//----------------------------------------------------------------------------------------------------------------
		glBindTexture(GL_TEXTURE_2D, texture);
		// Убеждаемся, что активировали шейдер прежде, чем настраивать uniform-переменные/объекты_рисования
		lightingShader.use();
		//lightingShader.setVec3("objectColor", 0.8f, 0.2f, 0.8f);
		// Активация текстурного слота
		glActiveTexture(GL_TEXTURE0);
		// Привязка текстуры к активному слоту
		glBindTexture(GL_TEXTURE_2D, texture);
		lightingShader.setVec3("lightColor", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("lightPos", lightPos);
		lightingShader.setInt("texture_diffuse1", 0);

		// Преобразования Вида/Проекции
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom+50), 0.4f / 0.3f, 1.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		// Мировое преобразование
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.1f, -0.8f, 0.0f));
		lightingShader.setMat4("model", model);

		// Рендеринг куба
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Также отрисовываем наш объект-"лампочку" 
		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // куб меньшего размера
		lampShader.setMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//----------------------------------------------------------------------------------------------------------------
		lightingShader.setVec3("lightColor", 0.2f, 0.2f, 0.2f);
		lightingShader.setVec3("lightPos", lightPos);
		lightingShader.setInt("texture_diffuse1", 0);

		glBindTexture(GL_TEXTURE_2D, secondObjectTexture);
		lightingShader.use();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);
		glm::mat4 secondObjectModel = glm::mat4(1.0f);
		lightingShader.setMat4("model", secondObjectModel);

		glBindVertexArray(secondObjectVAO);
		glDrawArrays(GL_TRIANGLES, 0, 48);

		// Также отрисовываем наш объект-"лампочку" 
		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);
		secondObjectModel = glm::mat4(1.0f);
		secondObjectModel = glm::translate(secondObjectModel, lightPos);
		secondObjectModel = glm::scale(secondObjectModel, glm::vec3(0.2f));
		lampShader.setMat4("model", secondObjectModel);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 48);


		// glfw: обмен содержимым front- и back- буферов. Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Опционально: освобождаем все ресурсы, как только они выполнили свое предназначение
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	// glfw: завершение, освобождение всех выделенных ранее GLFW-реcурсов
	glfwTerminate();
	return 0;
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании кнопки мыши в данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Убеждаемся, что окно просмотра соответствует новым размерам окна.
	// Обратите внимание, ширина и высота будут значительно больше, чем указано, на Retina-дисплеях
	glViewport(0, 0, width, height);
}


// glfw: всякий раз, когда перемещается мышь, вызывается данная callback-функция
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // перевернуто, так как y-координаты идут снизу вверх

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: всякий раз, когда прокручивается колесико мыши, вызывается данная callback-функция
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
