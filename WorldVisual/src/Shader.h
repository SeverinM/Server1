#pragma once
#include "glad/glad.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		~Shader();
		void Use();
		inline int GetId() { return _id; }
		inline void SetFloat(const char * name, float value)
		{
			int location = glGetUniformLocation(_id, name);
			Use();
			glUniform1f(location,value);
		}

		inline void SetMatrix(const char * name , glm::mat4 mat)
		{
			Use();
			int location = glGetUniformLocation(_id, name);

			double dArray[16] = { 0.0 };

			const float* pSource = (const float*)glm::value_ptr(mat);
			for (int i = 0; i < 16; ++i)
				dArray[i] = pSource[i];

			glUniformMatrix4fv(location, 1,GL_FALSE,glm::value_ptr(mat));
		}
};
