#include "glfw/window.h"
#include "webgpu/instance.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include <memory>

int main(int, char **) {

  auto instance = std::make_unique<Instance>();

  if (!instance->success()) {
    return 1;
  }

  std::cout << "WGPU instance: " << instance << std::endl;

  if (!glfwInit()) {
    std::cerr << "Could not initialize GLFW!" << std::endl;
    return 1;
  }

  auto window =
      std::make_unique<Window>(640, 480, "GLFW Window in seperate file boi");

  if (!window->success()) {
    std::cerr << "Could not open window!" << std::endl;
    glfwTerminate();
    return 1;
  }

  while (!window->shouldClose()) {
    // Check whether the user clicked on the close button (and any other
    // mouse/key event, which we don't use so far)
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
