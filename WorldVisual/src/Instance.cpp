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
	_shader->SetMatrix("v", _cam->GetMatrix());
	_shader->SetMatrix("p", _mat);

	float vertices[] = {
		 0,0,0,
		 1,0,0,
		 0,1,0,
		 0,0,1,
		 0,1,1,
		 1,1,0,
		 1,0,1,
		 1,1,1
	};

	unsigned int indices[] = {
		//Under face
		0,1,2,
		2,1,5,
		//Above face
		3,6,4,
		4,7,6,
		//Front face
		0,3,1,
		3,6,1,
		//Back face
		2,5,4,
		4,7,5,
		//Left face
		0,2,3,
		2,4,3,
		//Right face
		1,5,6,
		5,7,6
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
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	return 0;
}