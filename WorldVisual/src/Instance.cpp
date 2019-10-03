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

void Instance::InitDatas()
{
	_shader = new Shader("./src/shader");

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	_vao = new VAO();
	VBO* vbo = new VBO();
	IndexedVBO* ebo = new IndexedVBO();

	_vao->Use();
	_vao->AddDatas(vbo,vertices,sizeof(vertices));
	_vao->AddIndices(ebo, indices, sizeof(indices));
	_vao->Unuse();
}

void Instance::Resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, 800, 600);
}

int Instance::Update(float elapsed)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	_shader->Use();
	_vao->Use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	return 0;
}