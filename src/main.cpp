#include <GLFW/glfw3.h>
#include <cstdint>
#include <functional>
#include <glfw3webgpu.h>
#include <iostream>
#include <memory>
#include <vector>
#include <webgpu/webgpu.h>

#define WEBGPU_CPP_IMPLEMENTATION
#include <webgpu/webgpu.hpp>

int main(int, char **) {
  auto instance = wgpu::createInstance(wgpu::InstanceDescriptor{});

  if (!instance) {
    return 1;
  }

  std::cout << "WGPU instance: " << instance << std::endl;

  if (!glfwInit()) {
    std::cerr << "Could not initialize GLFW!" << std::endl;
    return 1;
  }

  // We ask GLFW not to set up any graphics API, we'll do it manually
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  GLFWwindow *window =
      glfwCreateWindow(640, 480, "FLECS on these WINDOWS", NULL, NULL);

  if (!window) {
    std::cerr << "Could not open window!" << std::endl;
    glfwTerminate();
    return 1;
  }

  wgpu::Surface surface = glfwGetWGPUSurface(instance, window);

  const wgpu::RequestAdapterOptions requestAdapterOptions =
      WGPURequestAdapterOptions{
          .compatibleSurface = surface,
      };

  auto adapter = instance.requestAdapter(requestAdapterOptions);
  std::cout << "Got adapter: " << adapter << std::endl;

  const wgpu::DeviceDescriptor deviceDescriptor = WGPUDeviceDescriptor{
      .label = "My Device",
      .requiredFeaturesCount = 0,
      .defaultQueue.label = "Default Queue",
  };
  auto device = adapter.requestDevice(deviceDescriptor);

  auto queue = device.getQueue();

  const auto swapChainFormat = surface.getPreferredFormat(adapter);

  const wgpu::SwapChainDescriptor swapChainDesc = WGPUSwapChainDescriptor{
      .width = 640,
      .height = 480,
      .usage = wgpu::TextureUsage::RenderAttachment,
      .format = swapChainFormat,
      .presentMode = wgpu::PresentMode::Fifo,
  };
  auto swapChain = device.createSwapChain(surface, swapChainDesc);

  while (!glfwWindowShouldClose(window)) {
    // Check whether the user clicked on the close button (and any other
    // mouse/key event, which we don't use so far)
    glfwPollEvents();

    wgpu::TextureView nextTexture = swapChain.getCurrentTextureView();

    wgpu::CommandEncoderDescriptor commandEncoderDesc{};
    commandEncoderDesc.label = "Command Encoder";
    auto encoder = device.createCommandEncoder(commandEncoderDesc);

    const WGPURenderPassColorAttachment renderPassColorAttachment{
        .view = nextTexture,
        .resolveTarget = nullptr,
        .loadOp = wgpu::LoadOp::Clear,
        .storeOp = wgpu::StoreOp::Store,
        .clearValue = wgpu::Color{0.9, 0.1, 0.2, 1.0},
    };

    const wgpu::RenderPassDescriptor renderPassDesc = WGPURenderPassDescriptor{
        .colorAttachmentCount = 1,
        .colorAttachments = &renderPassColorAttachment,
        .depthStencilAttachment = nullptr,
        .timestampWriteCount = 0,
    };

    auto renderPass = encoder.beginRenderPass(renderPassDesc);
    renderPass.end();

    nextTexture.release();

    wgpu::CommandBufferDescriptor cmdBufferDescriptor{};
    cmdBufferDescriptor.label = "Command buffer";
    auto command = encoder.finish(cmdBufferDescriptor);
    queue.submit(command);

    swapChain.present();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
