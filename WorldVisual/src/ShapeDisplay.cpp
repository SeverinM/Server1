#include "ShapeDisplay.h"
#include "BasicPhysic.h"
#include <stdio.h>

using namespace s1;

ShapeDisplay::ShapeDisplay(VAO* vao, Shader* sh, unsigned int sizeElement, bool useIndex, TransfProxy* transfProxy)
{
	_vao = vao;
	_shader = sh;
	_size = sizeElement;
	_useIndex = useIndex;
	_proxy = transfProxy;
}

ShapeDisplay::~ShapeDisplay()
{
	delete _vao;
}

void ShapeDisplay::Render(Camera * cam, mat4 projection)
{
	_shader->Use();
	_shader->SetMatrix("v", cam->GetMatrix());
	_shader->SetMatrix("m", GetMatrix());
	_shader->SetMatrix("p", projection);
	_vao->Use();
	if (_useIndex)
		glDrawElements(GL_TRIANGLES, _size, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ShapeDisplay::SetPosition(vec3 newPosition, bool relative)
{
	if (relative)
		_position += newPosition;
	else
		_position = newPosition;
}


void ShapeDisplay::AddPhysic(float mass, BodyType bt)
{
	if (_proxy == NULL)
	{
		_proxy = new BasicPhysic(rp3d::Vector3(_position.x, _position.y, _position.z), rp3d::Vector3(_scale.x, _scale.y, _scale.z), mass);
		dynamic_cast<BasicPhysic*>(_proxy)->SetState(bt);
	}
}

mat4 ShapeDisplay::GetMatrix()
{
	Vector3 axis;
	float angle;

	mat4 modelMatrix = glm::identity<mat4>();
	if (_proxy != NULL)
	{
		_proxy->Update(0.1);
		modelMatrix = _proxy->GetMatrix();
		return modelMatrix;
	}

	modelMatrix = scale(modelMatrix, _scale);
	modelMatrix = translate(modelMatrix, _position);
	return modelMatrix;
}

void ShapeDisplay::SetScale(vec3 newScale, bool relative)
{
	if (relative)
		_scale += newScale;
	else
		_scale = newScale;
}