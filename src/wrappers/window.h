#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>
#include <webgpu/webgpu.h>

class Instance;

/**
 * @brief Managed GLFW Window
 *
 */
class Window {
  GLFWwindow *window;

public:
  Window(uint32_t width, uint32_t height, std::string title,
         GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);
  ~Window();

  bool shouldClose();

  WGPUSurface getSurface(const Instance &instance);

  /**
   * @brief Wether or not the window initialised successfully
   *
   * @return true if the window initialised successfully
   * @return false if not
   */
  bool success();
};
