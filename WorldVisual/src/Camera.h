#pragma once
#include "glm/glm.hpp"

using namespace glm;

class Camera
{
	private:
		vec3 _position;
		vec3 _forward;
		vec3 _right;
		vec3 _up;
		vec3 _lookAt;
		float _fov;
		float _height;
		float _width;

	public:
		Camera(float h, float w);
		void SetPosition(vec3 newPosition, bool relative = false);
		void LookAt(vec3 position);
		void Update();
		mat4 GetMatrix();
};