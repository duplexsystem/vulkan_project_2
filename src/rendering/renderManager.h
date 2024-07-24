//
// Created by duplexsystem on 7/23/24.
//

#ifndef RENDERER_H
#define RENDERER_H
#include "renderingPCH.h"


class renderManager {
#ifndef NDEBUG
    bool bUseValidationLayers = true;
#elif
    bool bUseValidationLayers = false;
#endif


    GLFWwindow *window;
    vkb::Instance vkbInstance;
    VkSurfaceKHR surface;
    vkb::PhysicalDevice vkbPhysicalDevice;
    vkb::Device vkbDevice;
    VkQueue graphicsQueue;
    uint32_t graphicsQueueFamily;
    vkb::Swapchain vkbSwapchain;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;

public:
    renderManager(int width, int height, const char *title);

    ~renderManager();
};


#endif //RENDERER_H
