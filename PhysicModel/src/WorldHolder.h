#pragma once
#include "reactphysics3d.h"

using namespace rp3d;

class WorldHolder
{
	private :
		static DynamicsWorld* world;

	public:
		static DynamicsWorld * GetInstance()
		{
			if (world == NULL)
			{
				world = new DynamicsWorld(Vector3(0.0, 0.0, -1.01));
			}
			return world;
		}
};