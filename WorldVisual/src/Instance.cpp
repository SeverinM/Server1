#include "Instance.h"
#include "glm/glm.hpp"
#include "WorldHolder.h"

using namespace s1;

std::unordered_map<GLFWwindow*, Instance*> Instance::allInstances = std::unordered_map<GLFWwindow*, Instance*>();
bool Instance::_contextInitialized = false;

Instance::Instance(unsigned int width , unsigned height)
{
	_rotationMode = false;
	//Context
	if (!_contextInitialized)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	_width = width;
	_height = height;
	_window = glfwCreateWindow(width, height, "Window", NULL, NULL);
	glfwMakeContextCurrent(_window);

	//Bind callbacks
	glfwSetFramebufferSizeCallback(_window, Resize);
	glfwSetKeyCallback(_window, Keyboard);
	glfwSetMouseButtonCallback(_window, MouseButton);
	glfwSetCursorPosCallback(_window, MouseCursor);

	_mat = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	allInstances[_window] = this;

	if (!_contextInitialized)
	{
		_contextInitialized = !_contextInitialized;
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
}

Instance::~Instance()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void Instance::Init(std::string path)
{ 
	glEnable(GL_DEPTH_TEST);
	_shader = new Shader(path);
	_cam = new Camera(_height, _width);
	_cam->SetPosition(vec3(10, 10, 20));

	axis[0] = Instance::AddCube(glm::vec3(), glm::vec3(100, 0.01, 0.01));
	axis[1] = Instance::AddCube(glm::vec3(), glm::vec3(0.01, 100, 0.01));
	axis[2] = Instance::AddCube(glm::vec3(), glm::vec3(0.01, 0.01, 100));

	Font::Init();
	Shader* shad = new Shader("./src/text");
	Font* ft = new Font("./src/arial.ttf");
	ft->LoadlAll();
	txt = new Text(ft, shad);
}

int Instance::Update(float elapsed)
{
	//Mouse handling
	if (_rotationMode)
	{
		_cam->Rotate(glm::vec3(0, 0, 1), _deltaPosition.x * elapsed * 0.1);
		_cam->Rotate(_cam->GetRight(), _deltaPosition.y * elapsed * 0.1);
	}

	_cam->Update(elapsed);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Display axis
	axis[0]->GetShader()->SetVec3("color", glm::vec3(1, 0, 0));
	axis[0]->Render(_cam, _mat);

	axis[1]->GetShader()->SetVec3("color", glm::vec3(0, 1, 0));
	axis[1]->Render(_cam, _mat);

	axis[2]->GetShader()->SetVec3("color", glm::vec3(0, 0, 1));
	axis[2]->Render(_cam, _mat);

	//Display all cubes
	_shader->SetVec3("color", glm::vec3());
	for (_it = _allShapes.begin(); _it != _allShapes.end(); _it++)
	{
		(*_it)->Render(_cam, _mat);
	}

	txt->Render("0123456789.", 50.0f, 50.0f, 2.0f);

	_deltaPosition = vec2();

	glfwSwapBuffers(_window);
	glfwPollEvents();

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

void Instance::Delete(ShapeDisplay* sd)
{
	_it = std::find(_allShapes.begin(), _allShapes.end(), sd);
	_allShapes.erase(_it);
	delete sd;
	sd = NULL;
}

ShapeDisplay * Instance::AddCube(vec3 position, vec3 size)
{
	ShapeDisplay* display = ShapeDisplay::CreateCube(_shader);
	display->SetPosition(position);
	display->SetScale(size);
	_allShapes.push_back(display);
	return display;
}
