#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"
#include "ShapeDisplay.h"

class Instance
{
	protected:
		GLFWwindow* _window;
		ShapeDisplay* _cube;
		Shader* _shader;
		glm::mat4 _mat;
		Camera* _cam;
		int _height;
		int _width;

	public :
		bool Init(unsigned int width, unsigned int height);
		void InitDatas();
		static void Resize(GLFWwindow* window,int width,int height);
		int Update(float elapsed);
		inline GLFWwindow * GetWindow() { return _window; }
};