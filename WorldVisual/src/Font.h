#pragma once
#include <map>
#include "Shader.h"
#include "Camera.h"
#include "VertexArray.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character
{
	GLuint textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	GLuint advance;
};

class Font
{
public :
	static void Init();
	Font(const char* name);
	Character GetBitmap(int asciiCode);
	void LoadlAll();
	void Free();

private : 
	FT_Face face;
	std::map<char, Character> allLetters;
	static bool _initialized;
	static FT_Library * ft;
};