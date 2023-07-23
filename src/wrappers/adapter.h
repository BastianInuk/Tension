#pragma once

#include <webgpu/webgpu.h>
#include <optional>
#include <memory>

class Instance;
class Device;

class Adapter
{
    WGPUAdapter adapter;
    bool requestEnded;
    std::shared_ptr<Device> device;

public:
    Adapter(const WGPURequestAdapterOptions &options, const Instance &instance);
    ~Adapter();

    void inspect() const;

    WGPUAdapter get() const;
    std::shared_ptr<Device> reqeustDevice(const WGPUDeviceDescriptor &descriptor);
};