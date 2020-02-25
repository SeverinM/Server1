#pragma once
#include "Shader.h"
#include "Camera.h"
#include "VertexArray.h"
#include "Font.h"

using namespace s1;

class Text
{
private :
	Font* _ft;
	GLuint _indexVao;
	Shader* _shader;
	GLuint _indexVbo;
	glm::mat4 projection;

public : 
	Text(Font* firstFont, Shader * shad);
	void Render(std::string text, GLfloat x, GLfloat y, GLfloat scale);
};