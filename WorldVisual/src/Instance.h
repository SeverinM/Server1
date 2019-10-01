#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Instance
{
	protected:
		GLFWwindow* _window;
	public :
		bool Init(unsigned int width, unsigned int height);
		static void Resize(GLFWwindow* window,int width,int height);
		int Update(float elapsed);
		inline GLFWwindow * GetWindow() { return _window; }
};