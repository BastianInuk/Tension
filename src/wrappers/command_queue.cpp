#include <iostream>

#include "command_queue.h"

CommandQueue::CommandQueue(WGPUQueue queue) : queue(queue) {
  auto onQueueWorkDone = [](WGPUQueueWorkDoneStatus status,
                            void * /* pUserData */) {
    std::cout << "Queued work finished with status: " << status << std::endl;
  };
  wgpuQueueOnSubmittedWorkDone(queue, onQueueWorkDone, nullptr /* pUserData */);
}

CommandQueue::~CommandQueue() {
#ifdef WEBGPU_BACKEND_DAWN
  wgpuCommandBufferRelease(command);
#endif
}

void CommandQueue::submit(const std::vector<WGPUCommandBuffer> &range) {
  wgpuQueueSubmit(this->queue, std::ranges::size(range), range.data());
}
