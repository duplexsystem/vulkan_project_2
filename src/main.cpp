

#include "rendering/renderManager.h"

int main() {
  constexpr int width = 800;
  constexpr int height = 600;
  const auto title = "Vulkan App";
  spdlog::info("mimalloc version: {}", mi_version());
  auto renderManagerInstance = new renderManager(width, height, title);
  delete renderManagerInstance;
  return 0;
}
