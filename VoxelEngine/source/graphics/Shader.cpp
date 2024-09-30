#include "Shader.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glew.h>
#include <glfw3.h>

Shader::Shader(unsigned int id)
	:
	id(id)
{}


Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::use()
{
	glUseProgram(id);
}

Shader* load_shader(std::string vertexFile, std::string fragmentFile)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexFile);
		fShaderFile.open(fragmentFile);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}

	catch (std::ifstream::failure& e)
	{
		std::cerr << "ERRER:SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return nullptr;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint succes;
	GLchar infolog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infolog);
		std::cerr << "SHADER::VERTEX: compilation failed" << std::endl;
		std::cerr << infolog << std::endl;
		return nullptr;
	}
	// Vertex Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infolog);
		std::cerr << "SHADER::FRAGMENT: compilation failed" << std::endl;
		std::cerr << infolog << std::endl;
		return nullptr;
	}

	// Shader Program

	GLuint id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		glGetProgramInfoLog(id, 512, nullptr, infolog);
		std::cerr << "SHADER::PROGRAM: linking failed" << std::endl;
		std::cerr << infolog << std::endl;

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		//glDeletePrograms(&id, 1);

		return nullptr;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return new Shader(id);
}