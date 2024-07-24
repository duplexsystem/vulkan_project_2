//
// Created by duplexsystem on 7/23/24.
//

#include "glfwWindow.h"

#include "../renderingPCH.h"

void glfwWindow::init() {
    GLFWallocator allocator;
    allocator.allocate = reinterpret_cast<GLFWallocatefun>(malloc);
    allocator.reallocate = reinterpret_cast<GLFWreallocatefun>(realloc);
    allocator.deallocate = reinterpret_cast<GLFWdeallocatefun>(free);
    allocator.user = nullptr;

    glfwInitAllocator(&allocator);
    if (glfwInit() != GLFW_TRUE) {
        const char *err;
        glfwGetError(&err);
        throw std::runtime_error(fmt::format("Failed to initialize GLFW: {}", err));
    }
}

VkSurfaceKHR glfwWindow::createSurface(const VkInstance instance, GLFWwindow *window) {
    auto surface = VkSurfaceKHR{};
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        const char *err;
        glfwGetError(&err);
        throw std::runtime_error(fmt::format("Failed to create window surface: {}", err));
    }

    return surface;
}


GLFWwindow *glfwWindow::createWindow(const int width, const int height, const char *title) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    const auto window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        const char *err;
        glfwGetError(&err);
        throw std::runtime_error(fmt::format("Failed to create GLFW window: {}", err));
    }
    return window;
}

void glfwWindow::cleanup(GLFWwindow *window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

