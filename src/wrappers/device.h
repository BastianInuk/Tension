#pragma once

#include <webgpu/webgpu.h>

class Device
{
    WGPUDevice device;

public:
    Device(WGPUDevice device);
    ~Device();

    WGPUDevice get() const;
};