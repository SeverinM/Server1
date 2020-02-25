#include "Font.h"

bool Font::_initialized = false;
FT_Library * Font::ft = nullptr;

void Font::Init()
{
	ft = new FT_Library();
	if (FT_Init_FreeType(ft))
		std::cout << "Could not init freetype" << std::endl;
	else
		_initialized = true;
}

Font::Font(const char* name)
{
	if (!_initialized)
	{
		throw std::exception("Freetype was not loaded");
	}

	if (FT_New_Face(*ft, name, 0, &face))
	{
		std::cout << "Couldn't load the font" << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void Font::LoadlAll()
{
	for (int i = 0; i < 128; i++)
	{
		GetBitmap(i);
	}
}

void Font::Free()
{
	FT_Done_Face(face);
	FT_Done_FreeType(*ft);
}

Character Font::GetBitmap(int asciiCode)
{
	if (FT_Load_Char(face, asciiCode, FT_LOAD_RENDER))
	{
		std::cout << "couldn't load glyph" << std::endl;
	}

	if (allLetters.find(asciiCode) == allLetters.end())
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		allLetters[asciiCode] = character;
	}

	return allLetters[asciiCode];
}