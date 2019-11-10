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

	rp3d::Transform trsf(rp3d::Vector3(0, 0, 0), rp3d::Quaternion::identity());
	cb = world->createCollisionBody(trsf);
	_position = position;
	_size = size;
	Vector3 halfExtent(size.x / 2, size.y / 2, size.z / 2);
	shape = new BoxShape(halfExtent);

	Transform identity = Transform::identity();
	cb->addCollisionShape(shape, identity);
}

void BasicPhysic::Update(float elapsed)
{
	_position = cb->getTransform().getPosition();
	float* value = (float*)glm::value_ptr(modelMatrix);
	cb->getTransform().getOpenGLMatrix(value);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(_size.x, _size.y, _size.z));
	modelMatrix = glm::translate(modelMatrix, glm::vec3());
}

void BasicPhysic::SetPosition(Vector3 newPosition, bool relative)
{
	rp3d::Vector3 position;
	if (relative)
	{
		position = cb->getTransform().getPosition();
	}
	position += newPosition;

	rp3d::Quaternion orientation = cb->getTransform().getOrientation();
	rp3d::Transform newTransform(position, orientation);
	cb->setTransform(newTransform);
}

void BasicPhysic::SetRotation(float xRot, float yRot, float zRot)
{
	cb->setTransform(Transform(_position, rp3d::Quaternion::fromEulerAngles(glm::radians(xRot), glm::radians(yRot), glm::radians(zRot))));
}