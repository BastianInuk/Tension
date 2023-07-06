#pragma once

#include <webgpu/webgpu.h>

class Instance {
  WGPUInstance instance;

public:
  Instance(WGPUInstanceDescriptor desc = {});
  ~Instance();

  bool success();
};