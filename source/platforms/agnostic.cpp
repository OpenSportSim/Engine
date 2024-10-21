#include <exception>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <OpenSportSim/window.hpp>
#include <OpenSportSim/opengl.hpp>
#include <OpenSportSim/vulkan.hpp>

using OpenGLRenderer = OpenSportSim::OpenGL::Renderer;

OpenSportSim::GraphicsRenderer::~GraphicsRenderer() = default;
OpenSportSim::GraphicsBuffer::~GraphicsBuffer() = default;

OpenSportSim::GLFWHandle::GLFWHandle(const char *str) {
    glfwWindowHintString(GLFW_COCOA_FRAME_NAME, str);
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, str);
    glfwWindowHintString(GLFW_X11_CLASS_NAME, str);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
}

OpenSportSim::GLFWHandle::~GLFWHandle() {
    glfwDestroyWindow((GLFWwindow*)this->window);
    glfwTerminate();
}

void *OpenSportSim::GLFWHandle::raw() const noexcept {
    return (void*)this->window;
}

void OpenSportSim::GLFWHandle::createWindow() {
    auto window = glfwCreateWindow(600, 600, "Client", NULL, NULL);
    if (window == NULL) {
        throw std::exception();
    }
    glfwShowWindow(window);
    this->window = (void*)window;
}

bool OpenSportSim::GLFWHandle::isOpen() const noexcept {
    return this->window != nullptr;
}

OpenSportSim::GLFWHandle *OpenSportSim::AgnosticWindow::getHandle() const noexcept {
    return this->handle;
}

OpenSportSim::AgnosticWindow::AgnosticWindow(const char *str) {
    using GLFWHandleGL = OpenSportSim::OpenGL::GLFWHandle;
    using GLFWHandleVK = OpenSportSim::Vulkan::GLFWHandle;
    using GLFWHandle = OpenSportSim::GLFWHandle;
    if (glfwInit() == GLFW_FALSE) {
        throw std::exception();
    }
    /* if (glfwVulkanSupported()) {
        this->handle = dynamic_cast<GLFWHandle*>(new GLFWHandleVK(str));
    } else { */
        this->handle = new GLFWHandleGL(str);
        this->renderer = new OpenGLRenderer();
}

OpenSportSim::AgnosticWindow::~AgnosticWindow() {
    delete this->renderer;
    delete this->handle;
}

void OpenSportSim::AgnosticWindow::hide() const noexcept {
    glfwHideWindow((GLFWwindow*)this->handle->raw());
}

void OpenSportSim::AgnosticWindow::show() const noexcept {
    glfwShowWindow((GLFWwindow*)this->handle->raw());
}

void OpenSportSim::AgnosticWindow::requestFocus() const noexcept {
    glfwRequestWindowAttention((GLFWwindow*)this->handle->raw());
}

void OpenSportSim::AgnosticWindow::close() const noexcept {
    glfwSetWindowShouldClose((GLFWwindow*)this->handle->raw(), GLFW_TRUE);
    glfwDestroyWindow((GLFWwindow*)this->handle->raw());
}

void OpenSportSim::AgnosticWindow::poll() noexcept {
    glfwPollEvents();
}

void OpenSportSim::AgnosticWindow::swap() noexcept {
    using GLFWHandleGL = OpenSportSim::OpenGL::GLFWHandle;
    if (dynamic_cast<GLFWHandleGL*>(this->handle) != nullptr) {
        glfwSwapBuffers((GLFWwindow*)this->handle->raw());
    }
}

bool OpenSportSim::AgnosticWindow::shouldClose() const noexcept {
    return glfwWindowShouldClose((GLFWwindow*)this->handle->raw()) == GLFW_TRUE;
}
