#include "Instance.h"

bool Instance::Init(unsigned int width, unsigned height)
{
	_window = glfwCreateWindow(width, height, "Window", NULL, NULL);
	if (_window == NULL)
	{
		return false;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, Resize);
	return true;
}

void Instance::Resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, 800, 600);
}

int Instance::Update(float elapsed)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	return 0;
}