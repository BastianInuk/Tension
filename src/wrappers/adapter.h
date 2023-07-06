#pragma once

#include <webgpu/webgpu.h>

class Instance;

class Adapter
{
    WGPUAdapter adapter;
    bool requestEnded;

public:
    Adapter(const WGPURequestAdapterOptions &options, const Instance &instance);
    ~Adapter();

    void inspect() const;

    WGPUAdapter get() const;
};