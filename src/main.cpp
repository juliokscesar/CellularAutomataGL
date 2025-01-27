#include <iostream>
#include <cstdint>

// GLAD must always be included before any header files that use OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "core/errors.h"

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
void setGLFWContext(GLFWwindow* window);
bool initGLAD();

void setupViewport(GLFWwindow* window, const WindowSpecs& winSpecs);
void renderLoop(GLFWwindow* window, WindowSpecs& winSpecs);

int main() {
    initGLFW();
    logd("GLFW initialized");
    
    WindowSpecs winSpecs{800, 600, "Hello World"};
    GLFWwindow* window = initWindow(winSpecs);
    logd("Window created");
    if (!window) {
        logf("Null window pointer");
        return _ERR_NULL_WINDOW;
    }        
    setGLFWContext(window);
    logd("Context set");

    if (!initGLAD()) {
        logf("Failed to initialize GLAD");
        return _ERR_GLAD_INIT;
    }
    logd("Initialized GLAD");

    setupViewport(window, winSpecs);
    while (!glfwWindowShouldClose(window)) 
        renderLoop(window, winSpecs);
    
    glCheckError();
    logi("Ending program normally");

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

    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
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

void setGLFWContext(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

bool initGLAD() {
    return (bool)gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void setupViewport(GLFWwindow* window, const WindowSpecs& winSpecs) {
    glViewport(0, 0, winSpecs.width, winSpecs.height);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void renderLoop(GLFWwindow* window, WindowSpecs& winSpecs) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    glfwSwapBuffers(window);
}