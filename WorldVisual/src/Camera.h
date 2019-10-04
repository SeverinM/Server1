#pragma once
#include "glm/glm.hpp"

using namespace glm;

namespace s1
{
	class Camera
	{
	private:
		vec3 _position;
		vec3 _forward;
		vec3 _right;
		vec3 _up;
		vec3 _lookAt;
		vec2 _speed;
		float _fov;
		float _height;
		float _width;

	public:
		Camera(float h, float w);
		void SetPosition(vec3 newPosition, bool relative = false);
		void ChangeVelocity(vec2 delta);

		void LookAt(vec3 position);
		void Update(float elapsed)
		{
			SetPosition(_right * _speed.x * elapsed, true);
			SetPosition(_forward * _speed.y * elapsed, true);
		}

		inline vec3 GetRight() { return _right; }
		void Rotate(vec3 around, float value);
		void UpdateMat();
		mat4 GetMatrix();
	};
}