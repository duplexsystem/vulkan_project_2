cmake_minimum_required(VERSION 3.28)
project(vcpkgtest CXX)

set(CMAKE_CXX_STANDARD 20)


add_executable(vcpkgtest src/main.cpp
        src/rendering/vulkan/vulkanLifecycle.cpp
        src/rendering/vulkan/vulkanLifecycle.h
        src/rendering/windowing/glfwWindow.cpp
        src/rendering/windowing/glfwWindow.h
        src/rendering/renderManager.cpp
        src/rendering/renderManager.h
        src/rendering/renderingPCH.h
        src/PCH.h
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/mimalloc)
target_link_libraries(vcpkgtest PRIVATE $<IF:$<TARGET_EXISTS:mimalloc-static>,mimalloc-static,mimalloc>)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/fmt)
target_link_libraries(vcpkgtest PRIVATE fmt::fmt)

set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/spdlog)
target_link_libraries(vcpkgtest PRIVATE spdlog::spdlog)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw)
target_link_libraries(vcpkgtest PRIVATE glfw)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/boxer)
target_link_libraries(vcpkgtest PRIVATE Boxer)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/vulkan)
target_link_libraries(vcpkgtest PRIVATE Vulkan::Headers)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/vulkanutilitylibraries)
target_link_libraries(vcpkgtest PRIVATE Vulkan::UtilityHeaders)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/vkbootstrap)
target_link_libraries(vcpkgtest PRIVATE vk-bootstrap::vk-bootstrap)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/volk)
target_link_libraries(vcpkgtest PRIVATE volk::volk volk::volk_headers)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/vulkanmemoryallocator)
target_link_libraries(vcpkgtest PRIVATE GPUOpen::VulkanMemoryAllocator)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
target_link_libraries(vcpkgtest PRIVATE glm)