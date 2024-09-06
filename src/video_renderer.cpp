#include "../include/video_renderer.hpp"

VideoRenderer::VideoRenderer(const std::string& filename, float width, float height)
{
    texture = new Texture();
    initFFmpeg(filename);
    setGLParameters(width, height);

}

VideoRenderer::VideoRenderer(const VideoRenderer& video) {
    // Copy simple data types
    videoStreamIndex = video.videoStreamIndex;
    pixelFormat = video.pixelFormat;
    width = video.width;
    height = video.height;
    VAO = video.VAO;
    VBO = video.VBO;
    EBO = video.EBO;

    // Deep copy for dynamic memory (if applicable)
    if (video.buffer) {
        buffer = new unsigned char[width * height * 3]; // Assuming 3 bytes per pixel (RGB)
        std::copy(video.buffer, video.buffer + (width * height * 3), buffer);
    } else {
        buffer = nullptr;
    }

    // For pointers to AV structures, depending on how FFmpeg expects them to be managed
    // Simple pointer assignment (shallow copy) might be used, or you might need to create new instances
    formatContext = video.formatContext;
    codecContext = video.codecContext;
    frame = video.frame;
    packet = video.packet;
    swsContext = video.swsContext;

    // Handle shader and texture copying
    texture = video.texture ? new Texture(*video.texture) : nullptr;
}

// Destructor: Cleanup resources
VideoRenderer::~VideoRenderer() {
    cleanup();
}

void VideoRenderer::readFrame() {
    int response;
    while (av_read_frame(formatContext, packet) >= 0) {
        if (packet->stream_index == videoStreamIndex) {
            response = avcodec_send_packet(codecContext, packet);
            if (response < 0) {
                std::cerr << "Error: Failed to send packet to decoder" << std::endl;
                av_packet_unref(packet);
                exit(EXIT_FAILURE);
            }

            response = avcodec_receive_frame(codecContext, frame);
            if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
                av_packet_unref(packet);
                continue;
            } else if (response < 0) {
                std::cerr << "Error: Failed to receive frame from decoder" << std::endl;
                av_packet_unref(packet);
                exit(EXIT_FAILURE);
            }

            int numBytes = av_image_get_buffer_size(pixelFormat, width, height, 1);
            if (!buffer) {
                buffer = new unsigned char[numBytes];
            }

            uint8_t* dstData[4] = { nullptr };
            int dstLinesize[4] = { 0 };
            av_image_fill_arrays(dstData, dstLinesize, buffer, pixelFormat, width, height, 1);

            sws_scale(swsContext, frame->data, frame->linesize, 0, height, dstData, dstLinesize);

            av_packet_unref(packet);
            break;
        }
        av_packet_unref(packet);
    }
}

void VideoRenderer::cleanup() {
    if (packet) av_packet_free(&packet);
    if (frame) av_frame_free(&frame);
    if (codecContext) avcodec_free_context(&codecContext);
    if (formatContext) avformat_close_input(&formatContext);
    if (swsContext) sws_freeContext(swsContext);
    if (buffer) delete[] buffer;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void VideoRenderer::initFFmpeg(const std::string& filename) {
    avformat_network_init();

    if (avformat_open_input(&formatContext, filename.c_str(), nullptr, nullptr) != 0) {
        std::cerr << "Error: Could not open video file " << filename << std::endl;
        cleanup();
        exit(EXIT_FAILURE);
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        std::cerr << "Error: Could not find stream information" << std::endl;
        cleanup();
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < formatContext->nb_streams; ++i) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex == -1) {
        std::cerr << "Error: Could not find a video stream" << std::endl;
        cleanup();
        exit(EXIT_FAILURE);
    }

    AVCodecParameters* codecParameters = formatContext->streams[videoStreamIndex]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(codecParameters->codec_id);
    if (!codec) {
        std::cerr << "Error: Unsupported codec!" << std::endl;
        cleanup();
        exit(EXIT_FAILURE);
    }

    codecContext = avcodec_alloc_context3(codec);
    if (!codecContext) {
        std::cerr << "Error: Could not allocate video codec context" << std::endl;
        cleanup();
        exit(EXIT_FAILURE);
    }

    if (avcodec_parameters_to_context(codecContext, codecParameters) < 0) {
        std::cerr << "Error: Could not copy codec parameters to codec context" << std::endl;
        cleanup();
        exit(EXIT_FAILURE);
    }

    if (avcodec_open2(codecContext, codec, nullptr) < 0) {
        std::cerr << "Error: Could not open codec" << std::endl;
        cleanup();
        exit(EXIT_FAILURE);
    }

    frame = av_frame_alloc();
    packet = av_packet_alloc();

    width = codecContext->width;
    height = codecContext->height;

    swsContext = sws_getContext(
        width, height, codecContext->pix_fmt,
        width, height, pixelFormat,
        SWS_BILINEAR, nullptr, nullptr, nullptr
    );
}

void VideoRenderer::setGLParameters(float npos_x, float npos_y){
    float vertices[] = {
        // positions       // texture coords
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,   // top right
        1.0f, -npos_y, 0.0f, 1.0f, 0.0f,   // bottom right
        -npos_x, -npos_y, 0.0f, 0.0f, 0.0f,   // bottom left
        -npos_x,  1.0f, 0.0f,  0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void VideoRenderer::update(int play) {
    if(play){
        readFrame();
        texture->setTexture(buffer, width, height);
    }
}

void VideoRenderer::setWindowSize(float npos_x, float npos_y){
    setGLParameters(npos_x, npos_y);
}