#include "encoder.h"
#include <webgpu/webgpu.h>

Encoder::Encoder(WGPUCommandEncoder encoder) : encoder(encoder) {}

Encoder::~Encoder() {
#ifdef WEBGPU_BACKEND_DAWN
  wgpuCommandEncoderRelease(encoder);
#endif
}

WGPUCommandEncoder Encoder::get() { return this->encoder; }

WGPURenderPassEncoder
Encoder::renderPassBegin(const WGPURenderPassDescriptor &descriptor) {
  return wgpuCommandEncoderBeginRenderPass(this->encoder, &descriptor);
}

WGPUCommandBuffer
Encoder::finish(const WGPUCommandBufferDescriptor &descriptor) {
  return wgpuCommandEncoderFinish(this->encoder, &descriptor);
}

void Encoder::insertDebugMark(std::string_view marker) {
  wgpuCommandEncoderInsertDebugMarker(this->encoder, marker.data());
}
