#ifndef _glfw3_webgpu_h_
#define _glfw3_webgpu_h_

#include <GLFW/glfw3.h>
#include <webgpu/webgpu.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get a WGPUSurface from a GLFW window.
 */
WGPUSurface glfwGetWGPUSurface(WGPUInstance instance, GLFWwindow *window);

#ifdef __cplusplus
}
#endif

#endif // _glfw3_webgpu_h_