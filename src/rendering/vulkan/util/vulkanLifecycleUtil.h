//
// Created by duplexsystem on 7/23/24.
//

#ifndef VULKANLIFECYCLEUTIL_H
#define VULKANLIFECYCLEUTIL_H

#include "../vulkanPCH.h"


#include "../struct/vulkanCommandStruct.h"


class vulkanLifecycleUtil {
public:
    static vkb::Instance createInstance(bool bUseValidationLayers,
                                        const char *title);

    static vkb::PhysicalDevice selectPhysicalDevice(vkb::Instance vkbInstance,
                                                    VkSurfaceKHR surface);

    static vkb::Device
    createLogicalDevice(const vkb::PhysicalDevice &vkbPhysicalDevice);

    static vkb::Swapchain
    createSwapchain(int width, int height,
                    const vkb::PhysicalDevice &vkbPhysicalDevice,
                    const vkb::Device &vkbDevice, const VkSurfaceKHR &surface);

    static void createCommands(uint32_t graphicsQueueFamily,
                               VkDevice device, FrameData *frames);
};

#endif // VULKANLIFECYCLEUTIL_H
