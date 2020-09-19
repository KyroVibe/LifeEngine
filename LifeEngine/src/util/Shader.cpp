#include "Shader.h"

namespace LifeEngine {

	Shader* Shader::DefaultShader = nullptr;

	Shader::Shader(unsigned int id) : shaderID(id) { }

	Shader::Shader(const std::string shaderPath) {
		ShaderProgramSource source = ParseShader(shaderPath);
		shaderID = CreateShader(source.VertexSouce, source.FragmentSouce);
	}

	Shader::~Shader() {
		glDeleteProgram(shaderID);
	}

}
