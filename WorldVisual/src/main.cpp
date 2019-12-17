#include "Instance.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "WorldHolder.h"

using namespace s1;

int main()
{
	Instance* instance = new Instance(800,600);
	instance->Init();
	ShapeDisplay * sd = instance->AddCube(glm::vec3(0,0,1), glm::vec3(0.5, 0.5, 0.5));
	sd->AddPhysic(1, rp3d::BodyType::KINEMATIC);
	ShapeDisplay* ground = instance->AddCube(glm::vec3(0, 0, -2), glm::vec3(10, 10, 0.1));

	while (!instance->Update(0.1))
	{
	}

	return 0;
}