//
// Created by duplexsystem on 7/23/24.
//

#include "vulkanManager.h"

#include "util/vulkanLifecycleUtil.h"
#include "windowing/utils/glfwLifecycleUtils.h"

vulkanManager::vulkanManager(int width, int height, const char *title) {
    try {
        glfwLifecycleUtils::createInstance();
        if (glfwVulkanSupported() != GLFW_TRUE) {
            show(fmt::format(
                     "Vulkan is not supported by this device. Ensure your hardware "
                     "supports Vulkan and your graphics drivers are up to date.",
                     title)
                 .c_str(),
                 fmt::format("Error initializing {} renderer.", title).c_str(),
                 boxer::Style::Error);
            return;
        }

        window = glfwLifecycleUtils::createWindow(width, height, title);
        vkbInstance =
                vulkanLifecycleUtil::createInstance(bUseValidationLayers, title);
        surface = glfwLifecycleUtils::createSurface(vkbInstance.instance, window);
        vkbPhysicalDevice =
                vulkanLifecycleUtil::selectPhysicalDevice(vkbInstance, surface);
        vkbDevice = vulkanLifecycleUtil::createLogicalDevice(vkbPhysicalDevice);

        auto graphicsQueueResult = vkbDevice.get_queue(vkb::QueueType::graphics);
        if (!graphicsQueueResult.has_value()) {
            throw std::runtime_error(
  fmt::format(
                     "Failed to get graphics queue from device: {}",
                     graphicsQueueResult.error().message()));
        }
        graphicsQueue = graphicsQueueResult.value();
        auto graphicsQueueFamilyResult =
                vkbDevice.get_queue_index(vkb::QueueType::graphics);
        if (!graphicsQueueFamilyResult.has_value()) {
            throw std::runtime_error(fmt::format("Failed to get graphics queue family index from device: {}",
                                                 graphicsQueueFamilyResult.error().message()));
        }
        graphicsQueueFamily = graphicsQueueFamilyResult.value();
        vkbSwapchain = vulkanLifecycleUtil::createSwapchain(
            width, height, vkbPhysicalDevice, vkbDevice, surface);
        auto swapchainImagesResult = vkbSwapchain.get_images();
        if (!swapchainImagesResult.has_value()) {
            throw std::runtime_error(fmt::format("Failed to get swapchain images: {}",
                                                 swapchainImagesResult.error().message()));
        }
        swapchainImages = swapchainImagesResult.value();
        auto swapchainImageViewsResult = vkbSwapchain.get_image_views();
        if (!swapchainImageViewsResult.has_value()) {
            throw std::runtime_error(fmt::format("Failed to get swapchain image views: {}",
                                                 swapchainImageViewsResult.error().message()));
        }
        swapchainImageViews = swapchainImageViewsResult.value();
    } catch (std::runtime_error &e) {
        show(e.what(),
             fmt::format("Error initializing {} renderer.", title).c_str(),
             boxer::Style::Error);
        return;
    }
}

void vulkanManager::run() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        draw();
    }
}

void vulkanManager::draw() {

}

vulkanManager::~vulkanManager() {
    vkDeviceWaitIdle(vkbDevice.device);

    vkbSwapchain.destroy_image_views(swapchainImageViews);
    destroy_swapchain(vkbSwapchain);

    destroy_surface(vkbInstance, surface);

    destroy_device(vkbDevice);

    destroy_instance(vkbInstance);

    glfwDestroyWindow(window);
    glfwTerminate();
}
