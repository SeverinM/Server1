#include "Instance.h"
#include "glm/glm.hpp"

using namespace s1;

std::unordered_map<GLFWwindow*, Instance*> Instance::allInstances = std::unordered_map<GLFWwindow*, Instance*>();

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

	//Bind callbacks
	glfwSetFramebufferSizeCallback(_window, Resize);
	glfwSetKeyCallback(_window, Keyboard);
	glfwSetMouseButtonCallback(_window, MouseButton);
	glfwSetCursorPosCallback(_window, MouseCursor);

	_mat = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	allInstances[_window] = this;
	return true;
}

void Instance::InitDatas()
{ 
	glEnable(GL_DEPTH_TEST);
	_shader = new Shader("./src/shader");
	_cam = new Camera(_height, _width);
	_cam->SetPosition(vec3(5, -1, 1));
	AddCube(vec3(0, 0, 0), vec3(1, 1, 1));
	AddCube(vec3(0, 0, -2), vec3(4, 4, 0.1));
}

int Instance::Update(float elapsed)
{
	if (_rotationMode)
	{
		_cam->Rotate(glm::vec3(0, 0, 1), _deltaPosition.x * elapsed * 0.1);
		_cam->Rotate(_cam->GetRight(), _deltaPosition.y * elapsed * 0.1);
	}

	_cam->Update(elapsed);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (_it = _allShapes.begin(); _it != _allShapes.end(); _it++)
	{
		(*_it)->Render(_cam, _mat);
	}
	_deltaPosition = vec2();
	return 0;
}

void Instance::Resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Instance* Instance::Find(GLFWwindow* window)
{
	const std::unordered_map<GLFWwindow * , Instance *>::iterator it = allInstances.find(window);
	if (it != allInstances.end())
	{
		return it->second;
	}
	return NULL;
}

void Instance::Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Instance* inst = Find(window);
	if (inst == NULL)
	{
		return;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(inst->GetWindow(), true);
	}

	if (key == GLFW_KEY_D)
	{
		if (action == GLFW_PRESS)
			inst->GetCam()->ChangeVelocity(vec2(SPEED_X_CAMERA, 0));
		if(action == GLFW_RELEASE)
			inst->GetCam()->ChangeVelocity(vec2(-SPEED_X_CAMERA, 0));
	}

	if (key == GLFW_KEY_A)
	{
		if (action == GLFW_PRESS)
			inst->GetCam()->ChangeVelocity(vec2(-SPEED_X_CAMERA, 0));
		if (action == GLFW_RELEASE)
			inst->GetCam()->ChangeVelocity(vec2(SPEED_X_CAMERA, 0));
	}

	if (key == GLFW_KEY_W)
	{
		if (action == GLFW_PRESS)
			inst->GetCam()->ChangeVelocity(vec2(0, SPEED_Y_CAMERA));
		if (action == GLFW_RELEASE)
			inst->GetCam()->ChangeVelocity(vec2(0, -SPEED_Y_CAMERA));
	}

	if (key == GLFW_KEY_S)
	{
		if (action == GLFW_PRESS)
			inst->GetCam()->ChangeVelocity(vec2(0, -SPEED_Y_CAMERA));
		if (action == GLFW_RELEASE)
			inst->GetCam()->ChangeVelocity(vec2(0, SPEED_Y_CAMERA));
	}
}

void Instance::MouseButton(GLFWwindow* window, int button, int action, int mods)
{
	Instance* inst = Find(window);
	if (inst == NULL)
	{
		return;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
			inst->SetRotation(true);
		else
			inst->SetRotation(false);
	}
}

void Instance::MouseCursor(GLFWwindow* window, double xpos, double ypos)
{
	Instance* inst = Find(window);
	if (inst == NULL)
	{
		return;
	}
	inst->SetDeltaMouse(xpos, ypos);
}

void Instance::AddCube(vec3 position, vec3 size)
{
	ShapeDisplay* display = ShapeDisplay::CreateCube(_shader);
	display->SetPosition(position);
	display->SetScale(size);
	_allShapes.push_back(display);
}
