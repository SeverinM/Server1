#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"
#include "ShapeDisplay.h"
#include <unordered_map>
#include <vector>

#define SPEED_X_CAMERA 0.5
#define SPEED_Y_CAMERA 0.5

namespace s1
{
	class Instance
	{
	protected:
		GLFWwindow* _window;
		Shader* _shader;
		glm::mat4 _mat;
		Camera* _cam;
		int _height;
		int _width;
		bool _rotationMode;
		glm::vec2 _lastPosition;
		glm::vec2 _deltaPosition;
		std::vector<ShapeDisplay*> _allShapes;
		std::vector<ShapeDisplay*>::iterator _it;

	public:
		bool Init(unsigned int width, unsigned int height);
		void InitDatas();
		void AddCube(vec3 position, vec3 size);
		int Update(float elapsed);
		inline GLFWwindow* GetWindow() { return _window; }
		inline Camera* GetCam() { return _cam; }
		inline void SetRotation(bool value) { _rotationMode = value; }
		inline bool GetRotation() { return _rotationMode; }
		inline void SetDeltaMouse(double xPos, double yPos)
		{
			_deltaPosition = vec2(_lastPosition.x - xPos, _lastPosition.y - yPos);
			_lastPosition = vec2(xPos, yPos);
		}

		static Instance* Find(GLFWwindow* window);
		static void Resize(GLFWwindow* window, int width, int height);
		static void Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseButton(GLFWwindow* window, int button, int action, int mods);
		static void MouseCursor(GLFWwindow* window, double xpos, double ypos);
		static std::unordered_map<GLFWwindow*, Instance*> allInstances;
	};
}