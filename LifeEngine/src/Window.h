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
#include "util/Shader.h"

#define LOG(x) std::cout << x << std::endl;

namespace LifeEngine {

    class ModernWindow {
    public:
        ModernWindow(int width, int height, const std::string defaultShaderPath) {
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

            Shader shader = Shader(defaultShaderPath);
            Shader::DefaultShader = &shader;

            float* positions = new float[8] {
                -1.5f, -0.5f,
                 0.5f, -0.5f,
                 0.5f,  0.5f,
                -0.5f,  0.5f,
            };

            unsigned int* indices = new unsigned int[6] {
                0, 1, 2,
                2, 3, 0
            };

            LOG("Creating RenderBuffer");

            RenderBuffer testBuffer = RenderBuffer((unsigned int)8, positions, (unsigned int)6, indices);
            RenderBuffer* testSquare = CreateSquare(2, 2);

            LOG("Compiling Shaders");
            
            shader.Bind();
            int location = glGetUniformLocation(shader.Program(), "u_Color");
            int cameraPos = glGetUniformLocation(shader.Program(), "cameraPosition");
            int aspectRatio = glGetUniformLocation(shader.Program(), "aspectRatio");
            int cameraScale = glGetUniformLocation(shader.Program(), "cameraScale");
            int cameraWidth = glGetUniformLocation(shader.Program(), "cameraWidth");
            int cameraHeight = glGetUniformLocation(shader.Program(), "cameraHeight");
            int objectRotation = glGetUniformLocation(shader.Program(), "rotation");

            // Idk reset everything
            GLCall(glBindVertexArray(0));
            GLCall(glUseProgram(0));
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
            
            float r = 0.0f;
            float theta = 0.0f;
            float increment = 0.05f;
            while (!ShouldClose()) {
                
                GLCall(glClear(GL_COLOR_BUFFER_BIT));
                GLCall(glViewport(0, 0, width, height));
                
                shader.Bind();
                GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
                // GLCall(glUniform4f(cameraPos, r, 0.0f, 0.0f, 0.0f));
                // GLCall(glUniform1f(cameraWidth, r));
                // GLCall(glUniform1f(cameraHeight, 1.0f));
                GLCall(glUniform1f(aspectRatio, (float)width / (float)height));
                GLCall(glUniform1f(cameraScale, 0.5f));
                GLCall(glUniform1f(objectRotation, theta));

                // testBuffer.Draw();
                testSquare->Draw();

                // LOG("Drew Elements");

                theta += 0.1;

                if (r > 1.0f)
                    increment = -0.01f;
                else if (r < 0.0f)
                    increment = 0.01f;

                r += increment;

                glfwSwapBuffers(windPtr);
                glfwPollEvents();
            }

            delete testSquare;

            // delete vertBuf;
            // delete indBuf;
        }
        ~ModernWindow() {
            // delete Shader::DefaultShader;
            glfwTerminate(); // I GOT LUCKKKYYYYY
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