#pragma once
#include "reactphysics3d.h"
#include "glm/glm.hpp"

using namespace rp3d;

class TransfProxy
{
	protected :
		Vector3 _position;
		Vector3 _size;
		Quaternion _rotation;
		glm::mat4 modelMatrix;

	public:
		virtual void Update(float elapsed) = 0;
		inline glm::mat4 GetMatrix() { return modelMatrix; }
};
