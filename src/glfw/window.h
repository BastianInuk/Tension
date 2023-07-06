#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>

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

  /**
   * @brief Wether or not the window initialised successfully
   *
   * @return true if the window initialised successfully
   * @return false if not
   */
  bool success();
};
