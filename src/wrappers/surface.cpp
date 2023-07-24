#include "surface.h"

#include "instance.h"
#include "window.h"

#include "../../vendors/glfw3webgpu/glfw3webgpu.h"

Surface::Surface(const Instance &instance, const Window &window) {
  this->surface = glfwGetWGPUSurface(instance.get(), window.get());
}

Surface::~Surface() { wgpuSurfaceRelease(this->surface); }

WGPUSurface Surface::get() const { return this->surface; }

WGPUTextureFormat Surface::preferredFormatFor(const Adapter &adapter) const {
  return wgpuSurfaceGetPreferredFormat(this->surface, adapter.get());
}