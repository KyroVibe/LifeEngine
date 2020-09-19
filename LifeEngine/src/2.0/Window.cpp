#include "Window.h"

#include <iostream>

namespace LifeEngine2 {

	Window::Window(int width, int height, const std::string title) {
        if (!glfwInit()) {
            std::cout << "Failed to init GLFW" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        mWidth = width;
        mHeight = height;

        /* Create a windowed mode window and its OpenGL context */
        mWindow = glfwCreateWindow(width, height, "Modern Window", NULL, NULL);
        if (!mWindow)
        {
            glfwTerminate();
            std::cout << "Failed to create window" << std::endl;
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(mWindow);

        glfwSwapInterval(1);

        if (GLEW_OK != glewInit()) {
            std::cout << "Failed to init GLEW" << std::endl;
            return;
        }
	}

	Window::~Window() {
		glfwTerminate();
	}

}
