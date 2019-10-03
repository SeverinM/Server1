#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "VertexBuffer.h"

class VAO
{
	protected:
		unsigned int _id;
		VBO* _vbo;
		IndexedVBO * _ebo;

	public:
		VAO()
		{
			glGenVertexArrays(1, &_id);
		}

		void Use()
		{
			glBindVertexArray(_id);
		}

		void Unuse()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void AddDatas(VBO * vbo,void * vertices,unsigned int size)
		{
			Use();
			vbo->SetData(vertices, size);
			vbo->AddCanal();
			_vbo = vbo;
		}

		void AddIndices(IndexedVBO* ebo, void* indices, unsigned int size)
		{
			Use();
			ebo->SetData(indices, size);
			_ebo = ebo;
		}
};