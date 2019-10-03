#include "Instance.h"

bool Instance::Init(unsigned int width, unsigned height)
{
	_width = width;
	_height = height;
	_window = glfwCreateWindow(width, height, "Window", NULL, NULL);
	if (_window == NULL)
	{
		return false;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, Resize);
	_mat = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	return true;
}

void Instance::InitDatas()
{ 
	_shader = new Shader("./src/shader");
	_cam = new Camera(_height, _width);
	_cam->SetPosition(vec3(2, 0, 2));
	_cube = ShapeDisplay::CreateCube(_shader);
}

void Instance::Resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int Instance::Update(float elapsed)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	_cube->Render(_cam, _mat);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	return 0;
}