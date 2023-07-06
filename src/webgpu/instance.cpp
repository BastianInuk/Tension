#include "instance.h"

Instance::Instance(WGPUInstanceDescriptor desc) {
  this->instance = wgpuCreateInstance(&desc);
}

Instance::~Instance() { wgpuInstanceRelease(this->instance); }

bool Instance::success() { return !!this->instance; }