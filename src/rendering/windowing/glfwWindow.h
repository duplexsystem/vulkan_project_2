//
// Created by duplexsystem on 7/23/24.
//

#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H
#include "../renderingPCH.h"

class glfwWindow {
public:
    static GLFWwindow *createWindow(int width, int height, const char *title);

    static void init();

    static VkSurfaceKHR createSurface(VkInstance instance, GLFWwindow *window);

    static void cleanup(GLFWwindow *window);
};


#endif //GLFWWINDOW_H
