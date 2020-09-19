#include "RenderBuffer.h"

namespace LifeEngine {

	RenderBuffer::RenderBuffer() : BufferShader(*Shader::DefaultShader) {
		Init();
	}

	RenderBuffer::RenderBuffer(unsigned int vertexCount, float* vertices, unsigned int indiceCount, unsigned int* indices)
		: BufferShader(*Shader::DefaultShader), Vertices(vertices), Indices(indices), VertexCount(vertexCount), IndiceCount(indiceCount) {
		Init();
	}

	RenderBuffer::RenderBuffer(Shader& shader, unsigned int vertexCount, float* vertices, unsigned int indiceCount, unsigned int* indices)
		: BufferShader(shader), Vertices(vertices), Indices(indices), VertexCount(vertexCount), IndiceCount(indiceCount) {
		Init();
	}

	RenderBuffer::~RenderBuffer() {
		if (vertexBuffer != nullptr) {
			delete vertexBuffer;
			delete indexBuffer;
		}
		GLCall(glDeleteVertexArrays(1, &vertexArray));

		delete Indices;
		delete Vertices;
	}

	void RenderBuffer::Init() {
		CreateVertexArray();
		if (Vertices != nullptr) {
			RefreshVertexBuffer();
			RefreshIndexBuffer();
		}
	}

	void RenderBuffer::Draw() {
		if (vertexBuffer != nullptr) {

			if (&BufferShader == nullptr) {
				Shader::DefaultShader->Bind();
			}
			else {
				BufferShader.Bind();
			}

			BindVertexArray();
			BindIndexBuffer();
			GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
		}
	}

	void RenderBuffer::CreateVertexArray() {
		GLCall(glGenVertexArrays(1, &vertexArray));
		GLCall(glBindVertexArray(vertexArray));
	}

	void RenderBuffer::RefreshVertexBuffer() {
		if (vertexBuffer != nullptr)
			delete vertexBuffer;
		GLCall(glBindVertexArray(vertexArray));
		vertexBuffer = new VertexBuffer(Vertices, VertexCount * sizeof(float));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	}

	void RenderBuffer::RefreshIndexBuffer() {
		if (indexBuffer != nullptr)
			delete indexBuffer;
		indexBuffer = new IndexBuffer(Indices, IndiceCount);
	}

	// static RenderBuffer* CreateSquare(float width, float height) 
}
