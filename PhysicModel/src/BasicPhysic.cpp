#include "BasicPhysic.h"
#include "WorldHolder.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>

BasicPhysic::BasicPhysic(Vector3 position, Vector3 size, float mass)
{
	world = WorldHolder::GetInstance();
	rb = world->createRigidBody(Transform(position,rp3d::Quaternion::fromEulerAngles(glm::degrees((float)(rand() % 100)), 0, 0)));
	_position = position;
	_size = size;
	Vector3 halfExtent(size.x / 2, size.y / 2, size.z / 2);
	shape = new BoxShape(halfExtent);
	rb->addCollisionShape(shape, rb->getTransform(), 1);

	const rp3d::Quaternion ori = rp3d::Quaternion::fromEulerAngles(10, 0, 0);
}

void BasicPhysic::Update(float elapsed)
{
	float* value = (float*)glm::value_ptr(modelMatrix);
	rb->getTransform().getOpenGLMatrix(value);
}