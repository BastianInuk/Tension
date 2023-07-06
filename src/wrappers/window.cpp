#include "window.h"
#include "glfw3webgpu.h"
#include "instance.h"

Window::Window(uint32_t width, uint32_t height, std::string title,
               GLFWmonitor *monitor, GLFWwindow *share) {
  this->window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
}

Window::~Window() { glfwDestroyWindow(this->window); }

bool Window::shouldClose() { return glfwWindowShouldClose(this->window); }

bool Window::success() { return !!this->window; }

WGPUSurface Window::getSurface(const Instance &instance) {
  return glfwGetWGPUSurface(*instance, this->window);
}