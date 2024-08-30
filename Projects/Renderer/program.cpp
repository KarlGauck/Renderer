#include "program.h"
#include "files.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

ShaderProgram::ShaderProgram(std::string vertSource, std::string fragSource)
{
	std::string vertShaderRaw = FileHandler::readFile(vertSource);
	std::string fragShaderRaw = FileHandler::readFile(fragSource);
	const char* vertShaderC = vertShaderRaw.c_str();
	const char* fragShaderC = fragShaderRaw.c_str();

    std::cout << vertShaderRaw << std::endl;
    std::cout << fragShaderRaw << std::endl;

	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vertShaderC, NULL);
	glShaderSource(fShader, 1, &fragShaderC, NULL);

	glCompileShader(vShader);
    shaderCompilationDebug(vShader);
	glCompileShader(fShader);
    shaderCompilationDebug(fShader);

    this->handle = glCreateProgram();
    glAttachShader(this->handle, vShader);
    glAttachShader(this->handle, fShader);
    glLinkProgram(this->handle);
    programLinkingDebug();

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void ShaderProgram::use()
{
    glUseProgram(this->handle);
}

void ShaderProgram::uniformMatrix4fv(std::string name, glm::mat4 matrix)
{
    unsigned int loc = glGetUniformLocation(this->handle, name.c_str());
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix));
}

void ShaderProgram::shaderCompilationDebug(unsigned int shader)
{
#ifdef DEBUG
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Error during shader compilation:\n" << infoLog << std::endl;
    }
#endif
}

void ShaderProgram::programLinkingDebug()
{
#ifdef DEBUG
    std::cout << "lol" << std::endl;
    int success;
    char infoLog[512];
    glGetProgramiv(this->handle, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(this->handle, 512, NULL, infoLog);
        std::cout << "Error during program linking:\n" << infoLog << std::endl;
    }
#endif
}

