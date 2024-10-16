#include <OpenSportSim/opengl.hpp>
#include <OpenSportSim/vulkan.hpp>
#include <OpenSportSim/window.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

OpenSportSim::Vulkan::GLFWHandle::GLFWHandle(const char *str) : OpenSportSim::GLFWHandle(str) {
    glfwInitVulkanLoader(vkGetInstanceProcAddr);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    this->createWindow();
}

OpenSportSim::OpenGL::GLFWHandle::GLFWHandle(const char *str) : OpenSportSim::GLFWHandle(str) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    this->createWindow();
    glfwMakeContextCurrent((GLFWwindow*)this->window);
}
