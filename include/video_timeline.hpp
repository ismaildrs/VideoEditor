#ifndef VIDEO_TIMELINE_HPP
#define VIDEO_TIMELINE_HPP

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

#include <memory>  // For std::unique_ptr
#include <chrono>  // For time representation
#include <iostream>

struct TimelineVisualComp {
    std::unique_ptr<AVFormatContext> formatContext = nullptr;
    std::unique_ptr<AVCodecContext> codecContext = nullptr;
    
    std::chrono::duration<float> startTime{0.0f}; // Start time of the video in seconds
    std::chrono::duration<float> endTime{0.0f};   // End time of the video in seconds
    std::chrono::duration<float> vdStartTime{0.0f}; // Video display start time
    std::chrono::duration<float> vdEndTime{0.0f};   // Video display end time

    // Optional: Add additional metadata if needed
    std::string filePath;
    std::string title;
};

class VideoTimeline{



};

#endif