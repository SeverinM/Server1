#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

template <class T>
class VBO
{
	protected:
		GLint _index = 0;

	public:
		VBO()
		{
			glGenBuffers(1, &_index);
		}

		virtual void ConfigureData()
		{
			glBindBuffer(GL_ARRAY_BUFFER, _index);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(T), (void*)0);
		}

		virtual void SetData(T* vertices, unsigned int size)
		{
			if (_index <= 0)
				return;

			glBindBuffer(Gl_ARRAY_BUFFER, _index);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		}
};