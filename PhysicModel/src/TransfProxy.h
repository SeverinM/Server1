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
		inline glm::vec3 GetPosition() { return glm::vec3(_position.x, _position.y, _position.z); }
		inline glm::vec3 GetScale() { return glm::vec3(_size.x, _size.y, _size.z); }
		inline glm::mat4 GetMatrix() { return modelMatrix; }
};
