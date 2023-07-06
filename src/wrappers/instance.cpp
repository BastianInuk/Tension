#include "instance.h"
#include "./../../vendors/glfw3webgpu/glfw3webgpu.h"
#include <cassert>
#include <webgpu/webgpu.h>

#include "adapter.h"

Instance::Instance(WGPUInstanceDescriptor desc)
{
  this->instance = wgpuCreateInstance(&desc);
}

Instance::~Instance() { wgpuInstanceRelease(this->instance); }

bool Instance::success() { return !!this->instance; }

Adapter Instance::requestAdapter(const WGPURequestAdapterOptions &options)
{
  return Adapter(options, *this);
}

WGPUInstance Instance::get() const { return this->instance; }