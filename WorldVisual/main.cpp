#include "src/Instance.h"
#include "src/Shader.h"
#include "src//VertexArray.h"
#include "src/VertexBuffer.h"

using namespace s1;

int main()
{
	Instance* instance = new Instance(800,600);
	instance->Init();

	while (!instance->Update(0.1) && !glfwWindowShouldClose(instance->GetWindow()))
	{
		glfwSwapBuffers(instance->GetWindow());
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}