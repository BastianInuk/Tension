#include "adapter.h"
#include "instance.h"

#include <cassert>
#include <iostream>

Adapter::Adapter(const WGPURequestAdapterOptions &options, const Instance &instance)
{
    auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status,
                                    WGPUAdapter adapter, char const *,
                                    void *pSelf)
    {
        Adapter &self = *reinterpret_cast<Adapter *>(pSelf);
        if (status == WGPURequestAdapterStatus_Success)
        {
            self.adapter = adapter;
        }
        self.requestEnded = true;
    };

    // Call to the WebGPU request adapter procedure
    wgpuInstanceRequestAdapter(instance.get() /* equivalent of navigator.gpu */,
                               &options, onAdapterRequestEnded,
                               (void *)this);

    assert(this->requestEnded);
}

Adapter::~Adapter()
{
    wgpuAdapterRelease(adapter);
}

void Adapter::inspect() const
{
    std::vector<WGPUFeatureName> features;
    size_t featureCount = wgpuAdapterEnumerateFeatures(adapter, nullptr);
    features.resize(featureCount);
    wgpuAdapterEnumerateFeatures(adapter, features.data());

    std::cout << "Adapter features:" << std::endl;
    for (auto f : features)
    {
        std::cout << " - " << f << std::endl;
    }

    WGPUSupportedLimits limits = {};
    limits.nextInChain = nullptr;
    bool success = wgpuAdapterGetLimits(adapter, &limits);
    if (success)
    {
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
    if (properties.driverDescription)
    {
        std::cout << " - driverDescription: " << properties.driverDescription
                  << std::endl;
    }
    std::cout << " - adapterType: " << properties.adapterType << std::endl;
    std::cout << " - backendType: " << properties.backendType << std::endl;
}

WGPUAdapter Adapter::get() const
{
    return this->adapter;
}
