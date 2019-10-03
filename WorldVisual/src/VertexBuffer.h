#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

class VBO
{
	protected:
		GLuint _index = 0;
		unsigned int _size = 0;
		const void* _vertices;
		unsigned int _cursorCanal = 0;

	public:
		VBO()
		{
			glGenBuffers(1, &_index);
		}

		virtual void AddCanal(void * offset = (void*)0)
		{
			glVertexAttribPointer(_cursorCanal, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), offset);
			glEnableVertexAttribArray(_cursorCanal);
		}

		virtual void SetData(const void * vertices, unsigned int size)
		{
			if (_index <= 0)
				return;

			glBindBuffer(GL_ARRAY_BUFFER, _index);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
			_vertices = vertices;
			_size = sizeof(vertices);
		}

		inline GLuint GetIndex() { return _index; }
		unsigned int GetSize() { return _size; }
		const void * GetVertices() { return _vertices; }
};

class IndexedVBO : public VBO
{
	public:
		IndexedVBO() : VBO() {};
		virtual void SetData(const void* indices, unsigned int size)
		{
			if (_index <= 0)
				return;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
			_vertices = indices;
			_size = sizeof(indices);
		}
};