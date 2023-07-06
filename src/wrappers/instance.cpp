#include "instance.h"
#include "./../../vendors/glfw3webgpu/glfw3webgpu.h"
#include <cassert>
#include <webgpu/webgpu.h>

Instance::Instance(WGPUInstanceDescriptor desc) {
  this->instance = wgpuCreateInstance(&desc);
}

Instance::~Instance() { wgpuInstanceRelease(this->instance); }

bool Instance::success() { return !!this->instance; }

WGPUAdapter Instance::requestAdapter(const WGPURequestAdapterOptions &options) {
  struct UserData {
    WGPUAdapter adapter = nullptr;
    bool requestEnded = false;
  };
  UserData userData;

  auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status,
                                  WGPUAdapter adapter, char const *,
                                  void *pUserData) {
    UserData &userData = *reinterpret_cast<UserData *>(pUserData);
    if (status == WGPURequestAdapterStatus_Success) {
      userData.adapter = adapter;
    }
    userData.requestEnded = true;
  };

  // Call to the WebGPU request adapter procedure
  wgpuInstanceRequestAdapter(this->instance /* equivalent of navigator.gpu */,
                             &options, onAdapterRequestEnded,
                             (void *)&userData);

  assert(userData.requestEnded);

  return userData.adapter;
}

WGPUInstance Instance::operator*() const { return this->instance; }