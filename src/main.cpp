#include "wrappers/instance.h"
#include "wrappers/window.h"
#include "wrappers/surface.h"
#include "wrappers/adapter.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include <memory>

int main(int, char **)
{
  WGPUInstanceDescriptor desc = {};
  desc.nextInChain = nullptr;
  auto instance = std::make_unique<Instance>(desc);

  if (!instance->success())
  {
    return 1;
  }

  std::cout << "WGPU instance: " << instance << std::endl;

  if (!glfwInit())
  {
    std::cerr << "Could not initialize GLFW!" << std::endl;
    return 1;
  }

  // We ask GLFW not to set up any graphics API, we'll do it manually
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  auto window = std::make_unique<Window>(
      640, 480, "It compiles, but CMake and VSCode is just being a lil' bitch");

  if (!window->success())
  {
    std::cerr << "Could not open window!" << std::endl;
    glfwTerminate();
    return 1;
  }

  const auto surface = window->getSurface(*instance);
  const auto adapter = instance->requestAdapter({.nextInChain = nullptr,
                                                 .compatibleSurface = surface.get()});

  adapter.inspect();

  std::cout << "Got adapter: " << adapter.get() << std::endl;

  while (!window->shouldClose())
  {
    // Check whether the user clicked on the close button (and any other
    // mouse/key event, which we don't use so far)
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
