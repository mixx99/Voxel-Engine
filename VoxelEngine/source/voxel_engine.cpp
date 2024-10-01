#include <iostream>

//#define GLEW_STATIC // for static glew

#include <glew.h>
#include <glfw3.h>

#include "graphics/Shader.h"
#include "window/Window.h"
#include "window/Events.h"

int WIDTH = 1280;
int HEIGHT = 720;


int main()
{
	Window::initialize(WIDTH, HEIGHT, "Window 2.0");
	Events::initialize();

	glClearColor(0, 0, 0, 1);

	Shader* shader = load_shader("res/main.glslv", "res/main.glslf");
	if (shader == nullptr)
	{
		std::cerr << "failed to load shader" << std::endl;
		Window::terminate();
		return 1;
	}

	while (!Window::isShouldClose())
	{
		Events::pullEvents();
		if (Events::jpressed(GLFW_KEY_ESCAPE))
		{
			Window::setShouldClose(true);
		}
		if (Events::jclicked(GLFW_MOUSE_BUTTON_1))
		{
			glClearColor(1, 0, 0, 1);
		}
		glClear(GL_COLOR_BUFFER_BIT);
		Window::swapBuffers();
	}
	Window::terminate();
	return 0;




}