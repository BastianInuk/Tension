#pragma once

#include "window.h"
#include <webgpu/webgpu.h>

class Adapter;

class Instance
{
  WGPUInstance instance;
  // WGPUSurface surface;

public:
  Instance(WGPUInstanceDescriptor desc);
  ~Instance();

  Adapter requestAdapter(const WGPURequestAdapterOptions &options);

  bool success();

  WGPUInstance get() const;
};