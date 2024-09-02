cmake_minimum_required(VERSION 3.10)

# Project name and version
project(VideoEditor VERSION 1.0)

# Set the C++ standard (optional, but recommended)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the header files directory to the include path
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find all source files in the src directory
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c)

# Create the executable from the source files
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the specified libraries and flags
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

# Set up tests (if using CTest)
enable_testing()
file(GLOB_RECURSE TEST_SOURCES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Get the file name without extension and directory
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    # Add the test executable
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    
    # Link the main project library/executable to the tests (if needed)
    target_link_libraries(${TEST_NAME} PRIVATE ${PROJECT_NAME} pthread glfw GLU GL Xrandr Xxf86vm Xi Xinerama X11 rt dl)
    
    # Add the test to the CTest suite
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Optionally install the executable
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
