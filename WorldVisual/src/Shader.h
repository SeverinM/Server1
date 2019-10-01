#pragma once
#include "glad/glad.h"
#include <string>

#define VERTEX_SHADER "/vs.txt"
#define FRAGMENT_SHADER "/fs.txt"
#define GEOMETRY_SHADER "/gs.txt"

class Shader
{
	protected:
		unsigned int _id;

	public:
		Shader(std::string nameFolder);
		void Use();
};
