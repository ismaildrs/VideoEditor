#ifndef VIDEO_PLAYER_HPP
#define VIDEO_PLAYER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "constants.hpp"
#include "shader_class.hpp"
#include "texture.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
}

class VideoPlayer {
public:
    VideoPlayer(const std::string& filename, unsigned int width, unsigned int height, const char* name);
    ~VideoPlayer();

    bool windowShouldClose();
    void update();

    int getWidth();
    int getHeight();

private:
    void readFrame();
    void drawTexture();
    void setGLParameters();
    void initDisplay(unsigned int width, unsigned int height, const char* name);
    void closeDisplay();
    void initFFmpeg(const std::string& filename);
    void cleanup();

    AVFormatContext* formatContext = nullptr;
    AVCodecContext* codecContext = nullptr;
    AVFrame* frame = nullptr;
    AVPacket* packet = nullptr;
    SwsContext* swsContext = nullptr;
    int videoStreamIndex = -1;
    AVPixelFormat pixelFormat = AV_PIX_FMT_RGB24;
    int width = 0, height = 0;
    GLFWwindow* window = nullptr;
    unsigned char* buffer = nullptr;
    Shader* shader=nullptr;
    Texture* texture=nullptr;
    unsigned int VAO, VBO, EBO;
};

#endif // VIDEO_PLAYER_HPP
