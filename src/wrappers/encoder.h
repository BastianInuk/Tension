#pragma once

#include <webgpu/webgpu.h>

#include <string_view>

class Encoder {
  WGPUCommandEncoder encoder;

public:
  Encoder(WGPUCommandEncoder encoder);
  ~Encoder();

  WGPUCommandEncoder get();

  WGPUCommandBuffer finish(const WGPUCommandBufferDescriptor &descriptor);

  WGPURenderPassEncoder
  renderPassBegin(const WGPURenderPassDescriptor &descriptor);

  void insertDebugMark(std::string_view marker);
};
