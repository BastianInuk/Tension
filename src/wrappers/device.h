#pragma once

#include "command_queue.h"
#include "encoder.h"
#include "surface.h"
#include <optional>
#include <webgpu/webgpu.h>

class Device {
  WGPUDevice device;
  std::optional<CommandQueue> commandQueue;

public:
  Device(WGPUDevice device);
  ~Device();

  WGPUDevice get() const;

  CommandQueue getQueue();
  Encoder createEncoder(const WGPUCommandEncoderDescriptor &encoderDesc);
  WGPUSwapChain createSwapChain(const Surface &surface,
                                const WGPUSwapChainDescriptor &descriptor);
};