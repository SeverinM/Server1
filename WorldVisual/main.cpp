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
	ShapeDisplay * sd = instance->AddCube(glm::vec3(2,2,2), glm::vec3(0.5, 0.5, 0.5));
	sd->AddPhysic(100);
	ShapeDisplay* ground = instance->AddCube(glm::vec3(0, 0, -2), glm::vec3(10, 10, 1));
	ground->AddPhysic(100, BodyType::KINEMATIC, glm::radians(10.0),0,0);

	while (!instance->Update(0.1))
	{
	}

	return 0;
}