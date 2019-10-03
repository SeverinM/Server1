#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "VertexArray.h"
#include "Shader.h"

class Instance
{
	protected:
		GLFWwindow* _window;
		VAO * _vao;
		Shader* _shader;

	public :
		bool Init(unsigned int width, unsigned int height);
		void InitDatas();
		static void Resize(GLFWwindow* window,int width,int height);
		int Update(float elapsed);
		inline GLFWwindow * GetWindow() { return _window; }
};