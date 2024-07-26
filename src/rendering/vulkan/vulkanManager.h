//
// Created by duplexsystem on 7/23/24.
//

#ifndef VULKANMANAGER_H
#define VULKANMANAGER_H
#include "vulkanPCH.h"
#include "struct/vulkanCommandStruct.h"


class vulkanManager {
#ifndef NDEBUG
    bool bUseValidationLayers = true;
#else
    bool bUseValidationLayers = false;
#endif

    int frameNumber{0};

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
    FrameData frames[FRAME_OVERLAP];

    FrameData &get_current_frame() { return frames[frameNumber % FRAME_OVERLAP]; };

public:
    vulkanManager(int width, int height, const char *title);

    void run();

    void draw();

    ~vulkanManager();
};


#endif //VULKANMANAGER_H
