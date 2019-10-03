#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(float h , float w) : _position(vec3()), _forward(vec3(0, 1, 0)), _up(vec3(0, 0, 1)), _right(vec3(1, 0, 0)),_fov(45) , _lookAt(vec3(0,1,0)) , _height(h) , _width(w)
{
}

void Camera::SetPosition(vec3 position, bool relative)
{
	if (relative)
		_position += position;
	else
		_position = position;

	Update();
}

void Camera::LookAt(vec3 position)
{
	_lookAt = position;
	Update();
}

void Camera::Update()
{
	_forward = glm::normalize(_lookAt - _position);
	_right = glm::normalize(glm::cross(_forward, vec3(0, 1, 0)));
	_up = glm::normalize(glm::cross(_right, _forward));
}

mat4 Camera::GetMatrix()
{
	mat4 mat = glm::lookAt(_position, _lookAt, vec3(0,0,1));
	return mat;
}