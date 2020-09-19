#pragma once

#include <iostream>

#include "GL/glew.h"

#define ASSERT(x) if (!(x)) __debugbreak();

namespace LifeEngine {

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall())

	static void GLClearError() { // TODO: Stack overflow error sometimes???
		while (glGetError() != GL_NO_ERROR);
	}

	static bool GLLogCall() {
		while (GLenum error = glGetError()) {
			std::cout << "[OpenGL Error] (" << error << std::endl;
			return false;
		}
		return true;
	}

}