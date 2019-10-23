#include "src/Instance.h"
#include "src/Shader.h"
#include "src//VertexArray.h"
#include "src/VertexBuffer.h"
#include "WorldHolder.h"

using namespace s1;

int main()
{
	Instance* instance = new Instance(800,600);
	instance->Init();
	ShapeDisplay * sd = instance->AddCube(glm::vec3(), glm::vec3(0.1, 0.1, 0.1));
	sd->AddPhysic(1);

	while (!instance->Update(0.1))
	{
		WorldHolder::GetInstance()->update(0.00000001);
	}

	return 0;
}