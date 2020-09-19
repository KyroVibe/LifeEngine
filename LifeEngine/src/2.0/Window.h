#pragma once

#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace LifeEngine2 {

	class Window {
	private:
		GLFWwindow* mWindow;
		int mWidth, mHeight;
	public:
		Window(int width, int height, const std::string title);
		~Window();

		void Clear();
		void SwapBuffers();

		void PollEvents();
		bool ShouldClose();

		void ViewPort(int x, int y, int width, int height);
	};

}
