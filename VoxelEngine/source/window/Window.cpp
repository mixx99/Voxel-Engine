
#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include "Window.h"

GLFWwindow* Window::window;

int Window::initialize(int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, "Window", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height);
	return 0;
}

bool Window::isShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::terminate()
{
	glfwTerminate();
}