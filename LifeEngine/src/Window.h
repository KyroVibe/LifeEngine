#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/RenderBuffer.h"
#include "util/Debug.h"

#define LOG(x) std::cout << x << std::endl;

/*

This window will be designed as a HD pixel window.
Meaning it will virtually wrap pixel coordinates to a customized grid.

*/
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

    class ModernWindow {
    public:
        ModernWindow(int width, int height, const std::string shaderPath) {
            if (!glfwInit()) {
                std::cout << "Failed to init GLFW" << std::endl;
                return;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            this->width = width;
            this->height = height;

            /* Create a windowed mode window and its OpenGL context */
            windPtr = glfwCreateWindow(width, height, "Modern Window", NULL, NULL);
            if (!windPtr)
            {
                glfwTerminate();
                std::cout << "Failed to create window" << std::endl;
                return;
            }

            /* Make the window's context current */
            glfwMakeContextCurrent(windPtr);

            glfwSwapInterval(1);

            if (GLEW_OK != glewInit()) {
                std::cout << "Failed to init GLEW" << std::endl;
                return;
            }

            float* positions = new float[8] {
                -0.5f, -0.5f,
                 0.5f, -0.5f,
                 0.5f,  0.5f,
                -0.5f,  0.5f,
            };

            unsigned int* indices = new unsigned int[6] {
                0, 1, 2,
                2, 3, 0
            };

            // unsigned int vao;
            // GLCall(glGenVertexArrays(1, &vao));
            // GLCall(glBindVertexArray(vao));

            // VertexBuffer vb(positions, 8 * sizeof(float));

            // std::cout << vao << std::endl;

            // glEnableVertexAttribArray(0);
            // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

            LOG("Creating RenderBuffer");

            RenderBuffer testBuffer = RenderBuffer((unsigned int)8, positions, (unsigned int)6, indices);
            RenderBuffer testSquare;
            CreateSquare(0.8, 1.4, &testSquare);

            // IndexBuffer ib(indices, 6);

            LOG("Generating buffers");

            // auto vertBuf = RenderBuffer.GenVertexBuffer();
            // GLCall(glEnableVertexAttribArray(0));
            // GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
            // auto indBuf = RenderBuffer.GenIndexBuffer();

            LOG("Compiling Shaders");

            ShaderProgramSource source = ParseShader(shaderPath);
            unsigned int shader = CreateShader(source.VertexSouce, source.FragmentSouce);
            GLCall(glUseProgram(shader));

            int location = glGetUniformLocation(shader, "u_Color");

            GLCall(glBindVertexArray(0));
            GLCall(glUseProgram(0));
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
            
            float r = 0.0f;
            float increment = 0.05f;
            while (!ShouldClose()) {
                
                GLCall(glClear(GL_COLOR_BUFFER_BIT));
                GLCall(glViewport(0, 0, width, height));

                GLCall(glUseProgram(shader));
                GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

                // GLCall(glBindVertexArray(vao));

                // (*vertBuf).Bind();
                // (*indBuf).Bind();
                // ib.Bind();

                // GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
                // glDrawArrays(GL_TRIANGLES, 0, 6);

                // vertBuf.Unbind();
                // indBuf.Unbind();

                testBuffer.Draw();
                testSquare.Draw();

                // LOG("Drew Elements");

                if (r > 1.0f)
                    increment = -0.05f;
                else if (r < 0.0f)
                    increment = 0.05f;

                r += increment;

                glfwSwapBuffers(windPtr);
                glfwPollEvents();
            }

            // delete vertBuf;
            // delete indBuf;

            glDeleteProgram(shader);
        }
        ~ModernWindow() {
            glfwTerminate(); // I GOT LUCKKKYYYYY
        }

        unsigned int CompileShader(const std::string& source, unsigned int type) {
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

        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
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

        void Clear() {
            glClear(GL_COLOR_BUFFER_BIT);
        }
        void SwapBuffers() {
            glfwSwapBuffers(windPtr);
        }
        bool ShouldClose() {
            return glfwWindowShouldClose(windPtr);
        }
        void PollEvents() {
            glfwPollEvents();
        }
    private:
        int width, height;
        GLFWwindow* windPtr = nullptr;
    };
}