#pragma once
#include "TransfProxy.h"

using namespace rp3d;

class BasicPhysic : public TransfProxy
{
	protected:
		DynamicsWorld* world;
		RigidBody * rb;
		CollisionShape* shape;

	public :
		BasicPhysic(Vector3 position, Vector3 size = Vector3(1, 1, 1), float mass = 1);
		void Update(float elapsed);
		inline void SetState(BodyType bt)
		{
			rb->setType(bt);
		}
};