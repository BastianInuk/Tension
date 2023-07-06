#pragma once

#include <webgpu/webgpu.h>

class Instance;
class Window;

class Surface
{
    WGPUSurface surface;

public:
    Surface(const Instance &instance, const Window &window);
    ~Surface();

    WGPUSurface get() const;
};