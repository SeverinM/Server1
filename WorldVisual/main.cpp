#include "src/Instance.h"
#include "src/Shader.h"
#include "src//VertexArray.h"
#include "src/VertexBuffer.h"

#include "reactphysics3d.h"

using namespace s1;

int main()
{
	rp3d::DynamicsWorld * world = new rp3d::DynamicsWorld(rp3d::Vector3(0, -9.8, 0));
	Instance* instance = new Instance(800,600);
	instance->Init();
	instance->AddCube(glm::vec3(), glm::vec3(0.1, 0.1, 0.1));

	while (!instance->Update(0.1))
	{
	}

	return 0;
}