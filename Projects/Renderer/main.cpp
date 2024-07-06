#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "linmath.h"
#include "files.h"
 
 
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void shaderCompilationDebug(unsigned int shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Error during shader compilation:\n" << infoLog << std::endl;
    }
}

static void programLinkingDebug(unsigned int program)
{
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Error during program linking:\n" << infoLog << std::endl;
    }
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
 
int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    float vertices[] = {
     -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f
    };

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vShaderSource = FileHandler::readFile("C:/Users/kgauc/dev/Renderer/Projects/Renderer/shader/vertexShader.glsl");
    std::string fShaderSource = FileHandler::readFile("C:/Users/kgauc/dev/Renderer/Projects/Renderer/shader/fragmentShader.glsl");
    const char* vShaderCStyle = vShaderSource.c_str();
    const char* fShaderCStyle = fShaderSource.c_str();

	/*const char* vShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";*/

    /*const char* fShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
			"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}";p*/

    glShaderSource(vShader, 1,  &vShaderCStyle, NULL);
    glShaderSource(fShader, 1,  &fShaderCStyle, NULL);

    std::cout << vShaderSource << std::endl;
    std::cout << fShaderSource << std::endl;

    glCompileShader(vShader);
    shaderCompilationDebug(vShader);
    glCompileShader(fShader);
    shaderCompilationDebug(fShader);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    programLinkingDebug(program);
    glUseProgram(program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.f, 0.f, 0.f, 0.f);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
