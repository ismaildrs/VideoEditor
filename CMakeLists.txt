cmake_minimum_required(VERSION 3.10)

# Project name and version
project(VideoEditor VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for headers
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib/imgui
    ${PROJECT_SOURCE_DIR}/lib/imgui/backends
)

# Find all source files in the src directory
file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
)

# Collect ImGui source files
file(GLOB IMGUI_SOURCES
    ${PROJECT_SOURCE_DIR}/lib/imgui/*.cpp
    ${PROJECT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp
)

# Create the main executable from the source files
add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})

# Link the specified libraries to the main executable
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    pthread
    glfw
    GLU
    GL
    Xrandr
    Xxf86vm
    Xi
    Xinerama
    X11
    rt
    dl
    avformat 
    avcodec 
    avutil 
    swscale 
    png
)
