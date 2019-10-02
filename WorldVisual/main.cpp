#include "src/Instance.h"
#include "src/Shader.h"

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

	if (!instance->Init(500, 500))
	{
		return 2;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return 1;
	}

	Shader sh("./src/shader");
	while (!instance->Update(0.1) && !glfwWindowShouldClose(instance->GetWindow()))
	{
		ProcessInput(instance->GetWindow());
		glfwSwapBuffers(instance->GetWindow());
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}