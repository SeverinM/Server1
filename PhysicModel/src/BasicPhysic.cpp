#include "BasicPhysic.h"
#include "WorldHolder.h"

BasicPhysic::BasicPhysic(Vector3 position, Vector3 size, float mass)
{
	world = WorldHolder::GetInstance();
	rb = world->createRigidBody(Transform(position, Matrix3x3()));
	_position = position;
	_size = size;
}

void BasicPhysic::Update(float elapsed)
{

}