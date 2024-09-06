#ifndef VIDEO_CONTROLLER_HPP
#define VIDEO_CONTROLLER_HPP

#include "video_renderer.hpp"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

struct VideoInfos{
    unsigned int npos_x;
    unsigned int npos_y;
    VideoRenderer* video;
};

class VideoPlayer{
public:
    VideoPlayer(unsigned int width, unsigned int height); //

    bool windowShouldClose();

    void setFilePath(const char* filePath);

    int addVideo(std::string& filePath); // Add a video to the queue
    int removeVideo(unsigned int videoId); // Remove a video from the queue
    void update();
    int videoPause(unsigned int videoId);
    int videoReplay(unsigned int videoId);

private:

    void setupComponents();
    void closeDisplay();



    VideoInfos videoCont;
    unsigned int window_w;
    unsigned int window_h;

    unsigned int textureId;

    int play;
};


#endif