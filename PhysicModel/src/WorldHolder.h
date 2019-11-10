#pragma once
#include "reactphysics3d.h"

using namespace rp3d;

class WorldHolder
{
	private :
		static CollisionWorld * world;

	public:
		static CollisionWorld * GetInstance()
		{
			if (world == NULL)
			{
				world = new CollisionWorld();
			}
			return world;
		}
};