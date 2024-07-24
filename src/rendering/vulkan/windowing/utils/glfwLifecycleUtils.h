//
// Created by duplexsystem on 7/23/24.
//

#ifndef GLFWLIFECYCLEUTILS_H
#define GLFWLIFECYCLEUTILS_H
#include "../../vulkanPCH.h"

class glfwLifecycleUtils {
public:
  static void createInstance();

  static GLFWwindow *createWindow(int width, int height, const char *title);

  static VkSurfaceKHR createSurface(VkInstance instance, GLFWwindow *window);
};

#endif // GLFWLIFECYCLEUTILS_H
