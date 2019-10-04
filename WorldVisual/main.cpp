#include "src/Instance.h"
#include "src/Shader.h"
#include "src//VertexArray.h"
#include "src/VertexBuffer.h"

using namespace s1;

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	Instance* instance = new Instance();

	if (!instance->Init(800, 600))
	{
		return 2;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return 1;
	}
	else
	{
		instance->InitDatas();
	}


	while (!instance->Update(0.1) && !glfwWindowShouldClose(instance->GetWindow()))
	{
		glfwSwapBuffers(instance->GetWindow());
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}