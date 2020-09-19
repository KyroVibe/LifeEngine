#pragma once

#include "../util/Shader.h"

namespace LifeEngine {
	class Sprite {
	private:
		int mWidth, mHeight;
		unsigned int vertexBuffer, indexBuffer;
		Shader shader;
	public:
		Sprite(int width, int height);
		~Sprite();
	};
}
