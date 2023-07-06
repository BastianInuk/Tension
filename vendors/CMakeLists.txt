add_subdirectory(glfw)

# Include webgpu directory, to define the 'webgpu' target
add_subdirectory(webgpu)

add_subdirectory(glfw3webgpu)

# set_target_properties(webgpu PROPERTIES IMPORTED_LOCATION webgpu/macos-arm64/libwgpu.dylib)