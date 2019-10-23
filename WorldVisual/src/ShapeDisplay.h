#pragma once
#include "Shader.h"
#include "Camera.h"
#include "VertexArray.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "TransfProxy.h"

namespace s1
{

	class ShapeDisplay
	{
	protected:
		Shader* _shader;
		vec3 _position = vec3(0, 0, 0);
		quat _rotation = glm::identity<quat>();
		vec3 _scale = vec3(1, 1, 1);
		VAO* _vao;
		bool _useIndex = false;
		unsigned int _size = 0;
		TransfProxy* _proxy;

	public:
		ShapeDisplay(VAO* vao, Shader* sh, unsigned int sizeElement, bool useIndex, TransfProxy* transfProxy = NULL);
		~ShapeDisplay();
		void Render(Camera* cam, mat4 projection);
		void SetPosition(vec3 newPosition, bool relative = false);
		void SetScale(vec3 newScale, bool relative = false);
		void AddPhysic(float mass);
		mat4 GetMatrix();
		inline vec3 GetPosition() { return _position; }
		inline Shader* GetShader() { return _shader; }

		static ShapeDisplay* CreateCube(Shader* sh)
		{
			float vertices[] = {
				 0,0,0,
				 1,0,0,
				 0,1,0,
				 0,0,1,
				 0,1,1,
				 1,1,0,
				 1,0,1,
				 1,1,1
			};

			unsigned int indices[] = {
				//Under face
				0,1,2,
				2,1,5,
				//Above face
				3,6,4,
				4,7,6,
				//Front face
				0,3,1,
				3,6,1,
				//Back face
				2,5,4,
				4,7,5,
				//Left face
				0,2,3,
				2,4,3,
				//Right face
				1,5,6,
				5,7,6
			};

			VAO* vao = new VAO();
			VBO* vbo = new VBO();
			IndexedVBO* ebo = new IndexedVBO();

			vao->Use();
			vao->AddDatas(vbo, vertices, sizeof(vertices));
			vao->AddIndices(ebo, indices, sizeof(indices));
			vao->Unuse();
			return new ShapeDisplay(vao, sh, 36, true);
		}
	};
}