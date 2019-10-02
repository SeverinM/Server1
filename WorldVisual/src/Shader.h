#pragma once
#include "glad/glad.h"
#include <string>

#define VERTEX_SHADER "/vs.txt"
#define FRAGMENT_SHADER "/fs.txt"
#define GEOMETRY_SHADER "/gs.txt"

class Shader
{
	protected:
		unsigned int _id = 0;
		GLint CompileShader(std::string nameFolder, GLenum shaderType);

	public:
		Shader(std::string nameFolder);
		void Use();
};
