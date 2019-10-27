#include "BasicPhysic.h"
#include "WorldHolder.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iostream>

BasicPhysic::BasicPhysic(Vector3 position, Vector3 size, float mass)
{
	world = WorldHolder::GetInstance();
	const Quaternion quat = Quaternion::identity();
	rb = world->createRigidBody(Transform(position,quat));
	_position = position;
	_size = size;
	Vector3 halfExtent(size.x / 2, size.y / 2, size.z / 2);
	shape = new BoxShape(halfExtent);

	Transform identity = Transform::identity();
	rb->addCollisionShape(shape, identity, mass);
}

void BasicPhysic::Update(float elapsed)
{
	_position = rb->getTransform().getPosition();
	float* value = (float*)glm::value_ptr(modelMatrix);
	rb->getTransform().getOpenGLMatrix(value);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(_size.x, _size.y, _size.z));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-_size.x / 20.0, -_size.y / 20.0, -_size.z / 20.0));
}

void BasicPhysic::SetRotation(float xRot, float yRot, float zRot)
{
	rb->setTransform(Transform(_position, rp3d::Quaternion::fromEulerAngles(glm::radians(xRot), glm::radians(yRot), glm::radians(zRot))));
}