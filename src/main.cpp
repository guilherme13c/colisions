#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shader.hpp"

#ifndef SHADER_DIR
#define SHADER_DIR "../shader/"
#endif

constexpr char *VERTEX_SHADER = SHADER_DIR "vertex.glsl";
constexpr char *FRAGMENT_SHADER = SHADER_DIR "fragment.glsl";

int setupGLFW(GLFWwindow **window);
void mainLoop(GLFWwindow *window, GLuint programId, GLuint vertexbuffer);

int main() {
    GLFWwindow *window;
    if (setupGLFW(&window) != 0) {
        return -1;
    }

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLuint VertexArrayId;
    glGenVertexArrays(1, &VertexArrayId);
    glBindVertexArray(VertexArrayId);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint programId = LoadShaders(VERTEX_SHADER, FRAGMENT_SHADER);

    mainLoop(window, programId, vertexbuffer);

    return 0;
}

int setupGLFW(GLFWwindow **window) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(1200, 900, "Colisions", nullptr, nullptr);
    if (*window == nullptr) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(*window);

    return 0;
}

void mainLoop(GLFWwindow *window, GLuint programId, GLuint vertexbuffer) {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programId);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, (void *)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    };
}
