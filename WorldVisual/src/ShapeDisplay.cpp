#include "ShapeDisplay.h"

using namespace s1;

ShapeDisplay::ShapeDisplay(VAO* vao, Shader* sh, unsigned int sizeElement, bool useIndex)
{
	_vao = vao;
	_shader = sh;
	_size = sizeElement;
	_useIndex = useIndex;
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

mat4 ShapeDisplay::GetMatrix()
{
	mat4 modelMatrix = glm::identity<mat4>();
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