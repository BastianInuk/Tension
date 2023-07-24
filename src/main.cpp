#include "wrappers/adapter.h"
#include "wrappers/command_queue.h"
#include "wrappers/device.h"
#include "wrappers/instance.h"
#include "wrappers/surface.h"
#include "wrappers/window.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <webgpu/webgpu.h>

int main(int, char **) {
  auto instance = std::make_unique<Instance>(WGPUInstanceDescriptor{});

  if (!instance->success()) {
    return 1;
  }

  std::cout << "WGPU instance: " << instance << std::endl;

  if (!glfwInit()) {
    std::cerr << "Could not initialize GLFW!" << std::endl;
    return 1;
  }

  // We ask GLFW not to set up any graphics API, we'll do it manually
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  auto window = std::make_unique<Window>(640, 480, "Window");

  if (!window->success()) {
    std::cerr << "Could not open window!" << std::endl;
    glfwTerminate();
    return 1;
  }

  const auto surface = window->getSurface(*instance);
  auto adapter = instance->requestAdapter(
      {.nextInChain = nullptr, .compatibleSurface = surface.get()});

  adapter.inspect();

  std::cout << "Got adapter: " << adapter.get() << std::endl;

  auto device = adapter.reqeustDevice({.label = "My Device",
                                       .requiredFeaturesCount = 0,
                                       .defaultQueue.label = "Default Queue"});

  auto queue = device->getQueue();

  const auto swapchainFormat = surface.preferredFormatFor(adapter);

  const auto swapChain = device->createSwapChain(
      surface, {
                   // TODO: resize on resize
                   .width = 640,
                   .height = 480,
                   .format = swapchainFormat,
                   .usage = WGPUTextureUsage_RenderAttachment,
                   .presentMode = WGPUPresentMode_Fifo,
               });

  while (!window->shouldClose()) {
    // Check whether the user clicked on the close button (and any other
    // mouse/key event, which we don't use so far)
    glfwPollEvents();

    WGPUTextureView nextTexture = wgpuSwapChainGetCurrentTextureView(swapChain);
    std::cout << "nextTexture: " << nextTexture << std::endl;

    WGPURenderPassColorAttachment renderPassColorAttachment = {};

    renderPassColorAttachment.view = nextTexture;
    renderPassColorAttachment.loadOp = WGPULoadOp_Clear;
    renderPassColorAttachment.storeOp = WGPUStoreOp_Store;
    renderPassColorAttachment.clearValue = WGPUColor{0.9, 0.1, 0.2, 1.0};

    auto encoder = device->createEncoder({.label = "My command encoder"});

    encoder.insertDebugMark("Do one thing");
    encoder.insertDebugMark("Do another thing");

    WGPURenderPassEncoder renderPass =
        encoder.renderPassBegin({.colorAttachmentCount = 1,
                                 .colorAttachments = &renderPassColorAttachment,
                                 .timestampWriteCount = 0});
    wgpuRenderPassEncoderEnd(renderPass);

    wgpuTextureViewRelease(nextTexture);

    std::cout << "Submitting command..." << std::endl;

    WGPUCommandBuffer command = encoder.finish({.label = "Command buffer"});
    queue.submit({command});

    wgpuSwapChainPresent(swapChain);
  }

  // TODO: make class so it auto release
  wgpuSwapChainRelease(swapChain);
  glfwTerminate();
  return 0;
}
