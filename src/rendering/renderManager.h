//
// Created by duplexsystem on 7/23/24.
//

#ifndef RENDERER_H
#define RENDERER_H
#include "vulkan/vulkanManager.h"

class renderManager {
  vulkanManager *vulkanManagerInstance;

public:
  renderManager(int width, int height, const char *title);

  ~renderManager();
};

#endif // RENDERER_H
