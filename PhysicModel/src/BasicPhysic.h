#pragma once
#include "TransfProxy.h"

using namespace rp3d;

class BasicPhysic : public TransfProxy
{
	protected:
		CollisionWorld * world;
		CollisionBody * cb;
		CollisionShape* shape;

	public :
		BasicPhysic(Vector3 position, Vector3 size = Vector3(1, 1, 1), float mass = 1);
		void Update(float elapsed);
		void SetRotation(float xRot, float yRot, float zRot);
		void SetPosition(Vector3 newPosition, bool relative = false);
		inline void SetState(BodyType bt)
		{
			cb->setType(bt);
		}
};