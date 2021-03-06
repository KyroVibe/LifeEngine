#pragma once

#include <vector>
#include <GL/glew.h>

#include "../util/Debug.h"
#include "RenderBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace LifeEngine {

	/*
	* Gotta rename this to a 2D Render Buffer. This is a render buffer used for 2d graphics.
	*/
	class RenderBuffer {
	public:
		RenderBuffer();
		RenderBuffer(unsigned int vertexCount, float* vertices, unsigned int indiceCount, unsigned int* indices);
		~RenderBuffer();

		void Draw();

		inline VertexBuffer& GetVertexBuffer() { return *vertexBuffer; }
		inline IndexBuffer& GetIndexBuffer() { return *indexBuffer; }

		inline void BindVertexArray() { GLCall(glBindVertexArray(vertexArray)); }
		inline void BindVertexBuffer() { vertexBuffer->Bind(); }
		inline void BindIndexBuffer() { indexBuffer->Bind(); }
		
		void RefreshVertexBuffer();
		void RefreshIndexBuffer();

		unsigned int VertexCount, IndiceCount;
		float* Vertices = nullptr;
		unsigned int* Indices;
	private:

		void Init();
		void CreateVertexArray();

		unsigned int vertexArray;
		VertexBuffer* vertexBuffer = nullptr;
		IndexBuffer* indexBuffer = nullptr;
	};

	static void CreateSquare(float width, float height, RenderBuffer* output) {
		float* ver = new float[8] {
			width / 2, height / 2,
			width / 2, -height / 2,
			-width / 2, -height / 2,
			-width / 2, height / 2
		};
		unsigned int* ind = new unsigned int[6]{
			0, 1, 2,
			2, 3, 0
		};
		(*output) = *(new RenderBuffer(8, ver, 6, ind));
	}

}
