//
// Created by duplexsystem on 7/23/24.
//

#ifndef VULKANINIT_H
#define VULKANINIT_H

#include "../renderingPCH.h"

class vulkanLifecycle {
public:
    static vkb::Instance createInstance(bool bUseValidationLayers, const char *title);

    static vkb::PhysicalDevice selectPhysicalDevice(vkb::Instance vkbInstance, VkSurfaceKHR surface);

    static vkb::Device createLogicalDevice(const vkb::PhysicalDevice &vkbPhysicalDevice);

    static vkb::Swapchain createSwapchain(int width, int height, const vkb::PhysicalDevice &vkbPhysicalDevice,
                                          const vkb::Device &vkbDevice, const VkSurfaceKHR &surface);
};


#endif //VULKANINIT_H
