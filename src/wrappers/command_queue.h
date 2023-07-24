#pragma once

#include <__iterator/concepts.h>
#include <iterator>
#include <ranges>
#include <vector>
#include <webgpu/webgpu.h>

class CommandQueue {
  WGPUQueue queue;

public:
  CommandQueue(WGPUQueue queue);
  ~CommandQueue();

  void submit(const std::vector<WGPUCommandBuffer> &range);
};
