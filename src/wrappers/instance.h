#pragma once

#include "window.h"
#include <webgpu/webgpu.h>

class Instance {
  WGPUInstance instance;
  WGPUSurface surface;

public:
  Instance(WGPUInstanceDescriptor desc);
  ~Instance();

  WGPUSurface getSurface(const Window *window);

  WGPUAdapter requestAdapter(const WGPURequestAdapterOptions &options);

  bool success();

  WGPUInstance operator*() const;
};