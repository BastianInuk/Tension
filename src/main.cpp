#include "wrappers/instance.h"
#include "wrappers/window.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include <memory>

void inspectAdapter(WGPUAdapter adapter);

int main(int, char **) {
  WGPUInstanceDescriptor desc = {};
  desc.nextInChain = nullptr;
  auto instance = std::make_unique<Instance>(desc);

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

  auto window =
      std::make_unique<Window>(640, 480, "GLFW Window in seperate file boi");

  if (!window->success()) {
    std::cerr << "Could not open window!" << std::endl;
    glfwTerminate();
    return 1;
  }

  auto surface = window->getSurface(*instance);

  // Adapter options: we need the adapter to draw to the window's surface
  WGPURequestAdapterOptions adapterOpts = {};
  adapterOpts.nextInChain = nullptr;
  adapterOpts.compatibleSurface = surface;

  auto adapter = instance->requestAdapter(adapterOpts);

  inspectAdapter(adapter);

  std::cout << "Got adapter: " << adapter << std::endl;

  while (!window->shouldClose()) {
    // Check whether the user clicked on the close button (and any other
    // mouse/key event, which we don't use so far)
    glfwPollEvents();
  }

  wgpuSurfaceRelease(surface);
  wgpuAdapterRelease(adapter);

  glfwTerminate();
  return 0;
}

void inspectAdapter(WGPUAdapter adapter) {
  std::vector<WGPUFeatureName> features;
  size_t featureCount = wgpuAdapterEnumerateFeatures(adapter, nullptr);
  features.resize(featureCount);
  wgpuAdapterEnumerateFeatures(adapter, features.data());

  std::cout << "Adapter features:" << std::endl;
  for (auto f : features) {
    std::cout << " - " << f << std::endl;
  }

  WGPUSupportedLimits limits = {};
  limits.nextInChain = nullptr;
  bool success = wgpuAdapterGetLimits(adapter, &limits);
  if (success) {
    std::cout << "Adapter limits:" << std::endl;
    std::cout << " - maxTextureDimension1D: "
              << limits.limits.maxTextureDimension1D << std::endl;
    std::cout << " - maxTextureDimension2D: "
              << limits.limits.maxTextureDimension2D << std::endl;
    std::cout << " - maxTextureDimension3D: "
              << limits.limits.maxTextureDimension3D << std::endl;
    std::cout << " - maxTextureArrayLayers: "
              << limits.limits.maxTextureArrayLayers << std::endl;
    std::cout << " - maxBindGroups: " << limits.limits.maxBindGroups
              << std::endl;
    std::cout << " - maxDynamicUniformBuffersPerPipelineLayout: "
              << limits.limits.maxDynamicUniformBuffersPerPipelineLayout
              << std::endl;
    std::cout << " - maxDynamicStorageBuffersPerPipelineLayout: "
              << limits.limits.maxDynamicStorageBuffersPerPipelineLayout
              << std::endl;
    std::cout << " - maxSampledTexturesPerShaderStage: "
              << limits.limits.maxSampledTexturesPerShaderStage << std::endl;
    std::cout << " - maxSamplersPerShaderStage: "
              << limits.limits.maxSamplersPerShaderStage << std::endl;
    std::cout << " - maxStorageBuffersPerShaderStage: "
              << limits.limits.maxStorageBuffersPerShaderStage << std::endl;
    std::cout << " - maxStorageTexturesPerShaderStage: "
              << limits.limits.maxStorageTexturesPerShaderStage << std::endl;
    std::cout << " - maxUniformBuffersPerShaderStage: "
              << limits.limits.maxUniformBuffersPerShaderStage << std::endl;
    std::cout << " - maxUniformBufferBindingSize: "
              << limits.limits.maxUniformBufferBindingSize << std::endl;
    std::cout << " - maxStorageBufferBindingSize: "
              << limits.limits.maxStorageBufferBindingSize << std::endl;
    std::cout << " - minUniformBufferOffsetAlignment: "
              << limits.limits.minUniformBufferOffsetAlignment << std::endl;
    std::cout << " - minStorageBufferOffsetAlignment: "
              << limits.limits.minStorageBufferOffsetAlignment << std::endl;
    std::cout << " - maxVertexBuffers: " << limits.limits.maxVertexBuffers
              << std::endl;
    std::cout << " - maxVertexAttributes: " << limits.limits.maxVertexAttributes
              << std::endl;
    std::cout << " - maxVertexBufferArrayStride: "
              << limits.limits.maxVertexBufferArrayStride << std::endl;
    std::cout << " - maxInterStageShaderComponents: "
              << limits.limits.maxInterStageShaderComponents << std::endl;
    std::cout << " - maxComputeWorkgroupStorageSize: "
              << limits.limits.maxComputeWorkgroupStorageSize << std::endl;
    std::cout << " - maxComputeInvocationsPerWorkgroup: "
              << limits.limits.maxComputeInvocationsPerWorkgroup << std::endl;
    std::cout << " - maxComputeWorkgroupSizeX: "
              << limits.limits.maxComputeWorkgroupSizeX << std::endl;
    std::cout << " - maxComputeWorkgroupSizeY: "
              << limits.limits.maxComputeWorkgroupSizeY << std::endl;
    std::cout << " - maxComputeWorkgroupSizeZ: "
              << limits.limits.maxComputeWorkgroupSizeZ << std::endl;
    std::cout << " - maxComputeWorkgroupsPerDimension: "
              << limits.limits.maxComputeWorkgroupsPerDimension << std::endl;
  }

  WGPUAdapterProperties properties = {};
  properties.nextInChain = nullptr;
  wgpuAdapterGetProperties(adapter, &properties);
  std::cout << "Adapter properties:" << std::endl;
  std::cout << " - vendorID: " << properties.vendorID << std::endl;
  std::cout << " - deviceID: " << properties.deviceID << std::endl;
  std::cout << " - name: " << properties.name << std::endl;
  if (properties.driverDescription) {
    std::cout << " - driverDescription: " << properties.driverDescription
              << std::endl;
  }
  std::cout << " - adapterType: " << properties.adapterType << std::endl;
  std::cout << " - backendType: " << properties.backendType << std::endl;
}
