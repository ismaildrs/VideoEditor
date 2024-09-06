#include "video_player.hpp"

VideoPlayer::VideoPlayer(unsigned int width, unsigned int height){
    videoCont.npos_x = 0.5;
    videoCont.npos_y= 0.5;
    videoCont.video = nullptr;
    play = false;
}

// This function assumes you have a texture ID (videoTextureID) that is updated with the current video frame
void VideoPlayer::setupComponents() {
    // Begin the ImGui window
    if (ImGui::Begin("Video Player", nullptr, /*ImGuiWindowFlags_NoResize |*/ ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse)) {
        
        // Set the position and size of the window
        ImVec2 windowPos(ImGui::GetIO().DisplaySize.x * 0.5f - 500, 0);
        ImGui::SetWindowPos(windowPos);
        ImVec2 windowSize(1000, 600);
        ImGui::SetWindowSize(windowSize);

        // Get the available content region size
        ImVec2 contentRegion = ImGui::GetContentRegionAvail();

        // Render the video frame texture
        // Ensure that videoTextureID is the ID of your OpenGL texture
        if(videoCont.video) ImGui::Image((void*)(intptr_t)textureId, ImVec2(contentRegion.x, contentRegion.y));

        // Add buttons below the video content
        ImGui::SetCursorPos(ImVec2((contentRegion.x - 200) * 0.5f, contentRegion.y - 40));  // Centered button position
        if (ImGui::Button("Play", ImVec2(100, 30))) {
            play = true;
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Pause", ImVec2(100, 30))) {
            play = false;
        }
    }
    ImGui::End();
}




void VideoPlayer::update(){
    setupComponents();
    if(videoCont.video) videoCont.video->update(play); 
}


void VideoPlayer::setFilePath(const char* filePath) {
    std::cout << filePath << std::endl;
    try {
        // Clean up any existing VideoRenderer
        if (videoCont.video != nullptr) {
            delete videoCont.video;
            videoCont.video = nullptr;
        }

        // Check if filePath is valid
        if (filePath == nullptr || strlen(filePath) == 0) {
            std::cerr << "Error: Invalid file path provided." << std::endl;
            return;
        }

        // Create a new VideoRenderer
        videoCont.video = new VideoRenderer(filePath, videoCont.npos_x, videoCont.npos_y);
        textureId = videoCont.video->getTextureId();
        play = true;
        videoCont.video->update(play);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}