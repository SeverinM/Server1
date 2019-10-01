#include "Shader.h"
#include <sys/stat.h>
#include <stdexcept>
#include "Utils.h"

Shader::Shader(std::string nameFolder)
{
	struct stat buffer;
	std::string vsName = nameFolder + VERTEX_SHADER;
	std::string fsName = nameFolder + FRAGMENT_SHADER;
	bool isValid = Utils::FileExist(vsName.c_str()) && Utils::FileExist(fsName.c_str());

	if (!isValid)
		throw std::invalid_argument("Cannot compile the shader, missing file");

	std::string gsName = nameFolder + GEOMETRY_SHADER;
	bool geometryExist = (stat(gsName.c_str(), &buffer) == 0);
}