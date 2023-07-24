#include "device.h"

#include "encoder.h"

Device::Device(WGPUDevice device) : device(device) {}

Device::~Device() { wgpuDeviceRelease(this->device); }

WGPUDevice Device::get() const { return this->device; }

CommandQueue Device::getQueue() {
  if (!this->commandQueue) {
    this->commandQueue = wgpuDeviceGetQueue(this->device);
  }

  return this->commandQueue.value();
}

Encoder Device::createEncoder(const WGPUCommandEncoderDescriptor &encoderDesc) {
  return wgpuDeviceCreateCommandEncoder(this->device, &encoderDesc);
}

WGPUSwapChain
Device::createSwapChain(const Surface &surface,
                        const WGPUSwapChainDescriptor &descriptor) {
  return wgpuDeviceCreateSwapChain(this->device, surface.get(), &descriptor);
}