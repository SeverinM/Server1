#include "ShapeDisplay.h"

ShapeDisplay::ShapeDisplay(VAO* vao, Shader* sh, unsigned int sizeElement, bool useIndex)
{
	_vao = vao;
	_shader = sh;
	_size = sizeElement;
	_useIndex = useIndex;
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

void ShapeDisplay::Translate(vec3 newPosition)
{
	_position += newPosition;
}

mat4 ShapeDisplay::GetMatrix()
{
	mat4 modelMatrix;
	translate(modelMatrix, _position);
	scale(modelMatrix, _scale);
	return modelMatrix;
}