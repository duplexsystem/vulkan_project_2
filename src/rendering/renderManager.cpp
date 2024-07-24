//
// Created by duplexsystem on 7/23/24.
//

#include "renderManager.h"

renderManager::renderManager(int width, int height, const char *title) {
  vulkanManagerInstance = new vulkanManager(width, height, title);
  vulkanManagerInstance->run();
}

renderManager::~renderManager() { delete vulkanManagerInstance; }
