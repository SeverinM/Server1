#pragma once
#include "reactphysics3d.h"

using namespace rp3d;

class TransfProxy
{
	protected :
		Vector3 _position;
		Vector3 _size;
		Quaternion _rotation;

	public:
		virtual void Update(float elapsed) = 0;
		inline Vector3 GetPosition() { return _position; };
		inline Vector3 GetSize() { return _size; };
};
