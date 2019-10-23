#include "BasicPhysic.h"
#include "WorldHolder.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

BasicPhysic::BasicPhysic(Vector3 position, Vector3 size, float mass)
{
	world = WorldHolder::GetInstance();
	rb = world->createRigidBody(Transform(position, Matrix3x3()));
	_position = position;
	_size = size;
}

void BasicPhysic::Update(float elapsed)
{
	float* value = (float*)glm::value_ptr(modelMatrix);
	rb->getTransform().getOpenGLMatrix(value);
}