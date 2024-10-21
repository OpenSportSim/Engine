#include <OpenSportSim/vulkan.hpp>
#include <OpenSportSim/window.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

OpenSportSim::Vulkan::GLFWHandle::GLFWHandle(const char *str) : OpenSportSim::GLFWHandle(str) {
    glfwInitVulkanLoader(vkGetInstanceProcAddr);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    this->createWindow();
}
