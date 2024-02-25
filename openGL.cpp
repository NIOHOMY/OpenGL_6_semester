
#include <GL/glew.h>
#include <glut.h>
#include <GL/glew.h>
#include <glut.h>
#include <GLFW/glfw3.h>
// 
#include <stdio.h>
#include <iostream>


const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    color = aColor;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

in vec3 color;

out vec4 fragColor;

void main()
{
    fragColor = vec4(color, 1.0);
}
)";

int main()
{
    // Инициализируем GLFW
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    // Создаем окно
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }

    // Создаем контекст OpenGL и привязываем его к окну
    glfwMakeContextCurrent(window);

    // Инициализируем GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        glfwTerminate();
        return 1;
    }

    // Массив вершин для треугольника
    GLfloat vertices[] = {
       0.0f,  0.5f, 0.0f, // Вершина 
       0.2f, 0.2f, 0.6f, // Цвет голуб
      -0.5f, -0.5f, 0.0f, // Вершина 
       0.2f, 0.2f, 0.6f, // Цвет
       0.5f, -0.5f, 0.0f, // Вершина 
       0.2f, 0.2f, 0.6f  // Цвет 
    };

    // Создаем буфер вершин и связываем его
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Создаем шейдерную программу
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Связываем атрибуты вершин с буфером вершин
    GLint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "aColor");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    // Основной цикл приложения
    while (!glfwWindowShouldClose(window)) {
        // Очищаем экран
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Используем нашу шейдерную программу
        glUseProgram(shaderProgram);

        // Рисуем треугольник
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Обновляем другие события, такие как обработка ввода
        glfwPollEvents();

        // Помещаем то, что мы нарисовали, на дисплей
        glfwSwapBuffers(window);
    }

    // Удаляем буфер вершин и шейдерную программу
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Закрываем окно и завершаем работу GLFW
    glfwTerminate();

    return 0;
}



//while (!glfwWindowShouldClose(window)) {
    //    // очищаем экран
    //    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    // обновить другие события, такие как обработка ввода
    //    glfwPollEvents();
    //    // поместите то, что мы рисовали, на дисплей
    //    glfwSwapBuffers(window);
    //}