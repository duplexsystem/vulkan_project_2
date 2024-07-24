//
// Created by duplexsystem on 7/23/24.
//

#include "vulkanLifecycle.h"

#include "../renderingPCH.h"


vkb::Instance vulkanLifecycle::createInstance(const bool bUseValidationLayers, const char *title) {
    if (auto volkResult = volkInitialize(); volkResult != VK_SUCCESS) {
        throw std::runtime_error(fmt::format("Failed to initialize volk: {}", string_VkResult(volkResult)));
    }

    vkb::InstanceBuilder builder;

    auto inst_ret = builder.set_app_name(title)
            .request_validation_layers(bUseValidationLayers).set_debug_callback(
                [](const VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                   const VkDebugUtilsMessageTypeFlagsEXT messageType,
                   const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                   void *)
            -> VkBool32 {
                    auto type = vkb::to_string_message_type(messageType);
                    switch (messageSeverity) {
                        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                            spdlog::debug("[{}] {}\n", type, pCallbackData->pMessage);
                            break;
                        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                            spdlog::info("[{}] {}\n", type, pCallbackData->pMessage);
                            break;
                        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                            spdlog::warn("[{}] {}\n", type, pCallbackData->pMessage);
                            break;
                        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                            spdlog::error("[{}] {}\n", type, pCallbackData->pMessage);
                            break;
                        default:
                            break;
                    }
                    return VK_FALSE;
                }
            )
            .require_api_version(1, 3, 0)
            .build();
    if (!inst_ret.has_value()) {
        throw std::runtime_error(fmt::format("Failed to create Vulkan instance: {}", inst_ret.error().message()));
    }
    const auto instance = inst_ret.value();
    volkLoadInstance(instance.instance);

    return instance;
}

vkb::PhysicalDevice vulkanLifecycle::selectPhysicalDevice(vkb::Instance vkbInstance, VkSurfaceKHR surface) {
    //vulkan 1.3 features
    VkPhysicalDeviceVulkan13Features features{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES};
    features.dynamicRendering = true;
    features.synchronization2 = true;

    //vulkan 1.2 features
    VkPhysicalDeviceVulkan12Features features12{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES};
    features12.bufferDeviceAddress = true;
    features12.descriptorIndexing = true;


    //use vkbootstrap to select a gpu.
    //We want a gpu that can write to the GLFW surface and supports vulkan 1.3 with the correct features
    vkb::PhysicalDeviceSelector selector{vkbInstance};
    auto physicalDevice = selector
            .set_minimum_version(1, 3)
            .set_required_features_13(features)
            .set_required_features_12(features12)
            .set_surface(surface)
            .select();

    if (!physicalDevice.has_value()) {
        throw std::runtime_error(
            fmt::format("Failed to select a physical device: {}", physicalDevice.error().message()));
    }

    return physicalDevice.value();
}

vkb::Device vulkanLifecycle::createLogicalDevice(const vkb::PhysicalDevice &vkbPhysicalDevice) {
    //create the logical device
    const vkb::DeviceBuilder deviceBuilder{vkbPhysicalDevice};

    auto vkbDevice = deviceBuilder.build();

    if (!vkbDevice.has_value()) {
        throw std::runtime_error(fmt::format("Failed to create logical device: {}", vkbDevice.error().message()));
    }

    return vkbDevice.value();
}

vkb::Swapchain vulkanLifecycle::createSwapchain(const int width, const int height,
                                                const vkb::PhysicalDevice &vkbPhysicalDevice,
                                                const vkb::Device &vkbDevice, const VkSurfaceKHR &surface) {
    vkb::SwapchainBuilder swapchainBuilder{vkbPhysicalDevice, vkbDevice, surface};

    constexpr auto _swapchainImageFormat = VK_FORMAT_B8G8R8A8_UNORM;
    auto swapchain = swapchainBuilder
            .set_desired_format(VkSurfaceFormatKHR{
                .format = _swapchainImageFormat, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
            })
            //use vsync present mode
            .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
            .set_desired_extent(width, height)
            .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
            .build();

    if (!swapchain.has_value()) {
        throw std::runtime_error(fmt::format("Failed to create swapchain", swapchain.error().message()));
    }

    return swapchain.value();
}
