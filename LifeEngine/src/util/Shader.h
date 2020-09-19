#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "Debug.h"

namespace LifeEngine {

    struct ShaderProgramSource {
        std::string VertexSouce;
        std::string FragmentSouce;
    };

    static ShaderProgramSource ParseShader(const std::string& filepath) {
        std::ifstream stream(filepath);

        enum class ShaderType {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
            }
            else {
                ss[(int)type] << line << '\n';
            }
        }

        return { ss[0].str(), ss[1].str() };
    }

    static unsigned int CompileShader(const std::string& source, unsigned int type) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int len;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
            char* message = (char*)alloca(len * sizeof(char));
            glGetShaderInfoLog(id, len, &len, message);
            std::cout << "Failed to compile shader:" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
        unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    /*
    * Keep in mind the deconstructor deletes the program
    */
	class Shader {
	public:
        Shader(unsigned int id);
		Shader(const std::string shaderPath);
        ~Shader();

        inline void Bind() { GLCall(glUseProgram(shaderID)); }
        inline void Unbind() { GLCall(glUseProgram(0)); }

        inline unsigned int Program() { return shaderID; }

        static Shader* DefaultShader;
    private:
        unsigned int shaderID;
	};

}
