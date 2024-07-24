//
// Created by duplexsystem on 7/23/24.
//

#include "renderManager.h"

#include "renderingPCH.h"


#include "vulkan/vulkanLifecycle.h"
#include "windowing/glfwWindow.h"

renderManager::renderManager(int width, int height, const char *title) {
    try {
        glfwWindow::init();
        if (glfwVulkanSupported() != GLFW_TRUE) {
            show(fmt::format(
                     "Vulkan is not supported by this device. Ensure your hardware supports Vulkan and your graphics drivers are up to date.",
                     title).c_str(), fmt::format("Error initializing {} renderer.", title).c_str(),
                 boxer::Style::Error);
            return;
        }

        window = glfwWindow::createWindow(width, height, title);
        vkbInstance = vulkanLifecycle::createInstance(bUseValidationLayers, title);
        surface = glfwWindow::createSurface(vkbInstance.instance, window);
        vkbPhysicalDevice = vulkanLifecycle::selectPhysicalDevice(vkbInstance, surface);
        vkbDevice = vulkanLifecycle::createLogicalDevice(vkbPhysicalDevice);
        graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
        graphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();
        vkbSwapchain = vulkanLifecycle::createSwapchain(width, height, vkbPhysicalDevice, vkbDevice, surface);
        swapchainImages = vkbSwapchain.get_images().value();
        swapchainImageViews = vkbSwapchain.get_image_views().value();
    } catch (std::runtime_error &e) {
        show(e.what(), fmt::format("Error initializing {} renderer.", title).c_str(), boxer::Style::Error);
        return;
    }
}

renderManager::~renderManager() {
    vkDeviceWaitIdle(vkbDevice.device);

    vkbSwapchain.destroy_image_views(swapchainImageViews);
    destroy_swapchain(vkbSwapchain);

    destroy_surface(vkbInstance, surface);

    destroy_device(vkbDevice);

    destroy_instance(vkbInstance);

    glfwWindow::cleanup(window);
}
