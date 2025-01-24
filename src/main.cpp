#include <iostream>
#include <cstdint>

// GLAD must always be included before any header files that use OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <griffinLog/griffinLog.hpp>

#include "errors.h"

struct WindowSpecs {
    uint32_t width;
    uint32_t height;
    std::string title;
};

void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void initGLFW();
GLFWwindow* initWindow(const WindowSpecs& winSpecs);
void setGLFWContext(GLFWwindow* window, const WindowSpecs& winSpecs);
bool initGLAD();

void renderLoop(GLFWwindow* window, WindowSpecs& winSpecs);

int main() {
    initGLFW();
    
    WindowSpecs winSpecs{800, 600, "Hello World"};
    GLFWwindow* window = initWindow(winSpecs);
    if (!window) {
        grflog::fatal("Null window pointer");
        return _ERR_NULL_WINDOW;
    }        
    setGLFWContext(window, winSpecs);
    grflog::info("Created window and set context");
    glCheckError();

    if (!initGLAD()) {
        grflog::fatal("Failed to initialize GLAD");
        return _ERR_GLAD_INIT;
    }
    grflog::info("Initialized GLAD");

    while (!glfwWindowShouldClose(window)) {
        grflog::info("New frame");
        renderLoop(window, winSpecs);
    }
    glCheckError();
    grflog::info("Ending program normally");

    glfwTerminate();
    return 0;
}

void initGLFW() {
    glfwInit();

    // Set OpenGL version (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Set core-profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* initWindow(const WindowSpecs& winSpecs) {
    GLFWwindow* window = glfwCreateWindow(
        winSpecs.width,
        winSpecs.height,
        winSpecs.title.c_str(),
        nullptr,
        nullptr
    );
    return window;
}

void setGLFWContext(GLFWwindow* window, const WindowSpecs& winSpecs) {
    glfwMakeContextCurrent(window);
    glViewport(0, 0, winSpecs.width, winSpecs.height);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

bool initGLAD() {
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void renderLoop(GLFWwindow* window, WindowSpecs& winSpecs) {
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    glfwSwapBuffers(window);
}