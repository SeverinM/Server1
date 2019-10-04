#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

using namespace s1;

Camera::Camera(float h , float w) : _position(vec3()), _forward(vec3(0, 1, 0)), _up(vec3(0, 0, 1)), _right(vec3(1, 0, 0)),_fov(45) , _lookAt(vec3(0,1,0)) , _height(h) , _width(w)
{
	_speed = vec2();
}

void Camera::SetPosition(vec3 position, bool relative)
{
	if (relative)
	{
		_position += position;
		_lookAt += position;
	}	
	else
		_position = position;

	UpdateMat();
}

void Camera::LookAt(vec3 position)
{
	_lookAt = position;
	UpdateMat();
}

void Camera::UpdateMat()
{
	_forward = glm::normalize(_lookAt - _position);
	_right = glm::normalize(glm::cross(_forward, vec3(0, 0, 1)));
	_up = glm::normalize(glm::cross(_right, _forward));
}

void Camera::ChangeVelocity(vec2 delta)
{
	_speed += delta;
}

mat4 Camera::GetMatrix()
{
	mat4 mat = glm::lookAt(_position, _lookAt, _up);
	return mat;
}

void Camera::Rotate(vec3 around, float value)
{
	_forward = glm::rotate(_forward, value, around);
	_lookAt = _position + _forward;
	UpdateMat();
}