//
// Created by duplexsystem on 7/24/24.
//

#ifndef VULKANCOMMANDSTRUCT_H
#define VULKANCOMMANDSTRUCT_H

#include "../vulkanPCH.h"

struct FrameData {
    VkCommandPool commandPool;
    VkCommandBuffer mainCommandBuffer;
};

constexpr unsigned int FRAME_OVERLAP = 2;

#endif //VULKANCOMMANDSTRUCT_H
