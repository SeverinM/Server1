#include "Shader.h"
#include <stdexcept>
#include "Utils.h"

Shader::Shader(std::string nameFolder)
{
	std::string vsName = nameFolder + VERTEX_SHADER;
	std::string fsName = nameFolder + FRAGMENT_SHADER;

	bool vsExist = Utils::FileExist(vsName.c_str());
	bool fsExist = Utils::FileExist(fsName.c_str());

	if (!(vsExist && fsExist))
		throw std::invalid_argument("Cannot compile the shader, missing file");

	//Optionnal we can add geometry shader
	std::string gsName = nameFolder + GEOMETRY_SHADER;
	bool geometryExist = Utils::FileExist(gsName.c_str());

	_id = glCreateProgram();
	unsigned int idVS = CompileShader(vsName, GL_VERTEX_SHADER);
	unsigned int idFS = CompileShader(fsName, GL_FRAGMENT_SHADER);

	//Successful compile
	if (idVS && idFS)
	{
		glAttachShader(_id, idVS);
		glAttachShader(_id, idFS);
		std::cout << _id << std::endl;
	}

	if (geometryExist)
	{
		unsigned int idGS = CompileShader(gsName, GL_GEOMETRY_SHADER);
		if (idGS != 0)
		{
			glAttachShader(_id, idGS);
		}
	}

	glLinkProgram(_id);
	glDeleteShader(idVS);
	glDeleteShader(idFS);
}

GLint Shader::CompileShader(std::string nameFolder, GLenum shaderType)
{
	struct StringHelper {
		const char* p;
		StringHelper(const std::string& s) : p(s.c_str()) {}
		operator const char** () { return &p; }
	};

	unsigned int shader;
	shader = glCreateShader(shaderType);
	stringstream* ss = Utils::ReadFile(nameFolder.c_str());
	glShaderSource(shader, 1, StringHelper(ss->str()), NULL);
	glCompileShader(shader);
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return 0;
	}
	return shader;
}

void Shader::Use()
{
	glUseProgram(_id);
}

Shader::~Shader()
{
	if (_id != 0)
		glDeleteProgram(_id);
}