cmake_minimum_required(VERSION 3.25)
project(
    LearnWebGPU # name of the project, which will also be the name of the visual studio solution if you use it
    VERSION 0.1.0 # any version number
    LANGUAGES CXX C # programming languages used by the project
)

add_executable(App
    src/wrappers/window.h
    src/wrappers/window.cpp
    src/wrappers/instance.h
    src/wrappers/instance.cpp
    src/wrappers/adapter.h
    src/wrappers/adapter.cpp
    src/wrappers/device.h
    src/wrappers/device.cpp
    src/wrappers/command_queue.h
    src/wrappers/command_queue.cpp
    src/wrappers/encoder.h
    src/wrappers/encoder.cpp
    src/wrappers/surface.h
    src/wrappers/surface.cpp
    src/main.cpp
)

add_subdirectory(vendors)
target_link_libraries(App PRIVATE glfw webgpu glfw3webgpu)

set_target_properties(App PROPERTIES
    CXX_STANDARD 20
    COMPILE_WARNING_AS_ERROR ON
)

include(utils.cmake)

target_treat_all_warnings_as_errors(App)

# The application's binary must find wgpu.dll or libwgpu.so at runtime,
# so we automatically copy it (it's called WGPU_RUNTIME_LIB in general)
# next to the binary.
target_copy_webgpu_binaries(App)
