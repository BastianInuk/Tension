#include "device.h"

Device::Device(WGPUDevice device)
    : device(device)
{
}

Device::~Device()
{
    wgpuDeviceRelease(this->device);
}

WGPUDevice Device::get() const
{
    return this->device;
}
