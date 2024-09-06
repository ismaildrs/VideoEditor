#ifndef IDR_EDITOR_HPP
#define IDR_EDITOR_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "video_player.hpp"
#include "file_manager.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class IdrEditor{
public:
    IdrEditor(unsigned int width, unsigned int height, const char* name);
    ~IdrEditor();
    bool windowShouldClose();

    void render();

private:
    void initImGui();
    void closeImGui();
    void initDisplay(unsigned int width, unsigned int height, const char* name) ;
    void closeDisplay();
    void initAudio();
    void closeAudio();
    void setupNewImGuiFrame();


    FileManager* fileManager = nullptr;
    VideoPlayer* videoPlayer = nullptr;
    GLFWwindow* window = nullptr;
    unsigned int window_w; //Window Width
    unsigned int window_h; // Window Height

};


#endif