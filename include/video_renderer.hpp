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


class VideoRenderer {
public:
    VideoRenderer(const std::string& filename, float npos_x = 0.0f, float npos_y=0.0f);
    VideoRenderer(const VideoRenderer&);
    ~VideoRenderer();

    unsigned int getTextureId(){
        if(texture) return texture->getTextureId();
    }

    void update(int);

    void setWindowSize(float npos_x, float npos_y);


private:
    void readFrame();
    void setGLParameters(float norm_w, float norm_h);
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
    unsigned char* buffer = nullptr;
    unsigned int VAO, VBO, EBO;
    Texture* texture=nullptr;

};

#endif // VIDEO_PLAYER_HPP
