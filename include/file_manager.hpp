#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <filesystem>
#include <vector>
#include <iostream>
#include <video_player.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

struct Dir {
    std::vector<std::filesystem::path> dirs;
    std::vector<std::string> files;
};

class FileManager {
public:
    FileManager(VideoPlayer*) ;
    
    void update();

private:
    void setCurrentDirComp();

    VideoPlayer* video;

    std::filesystem::path currentDir;
    Dir currentDirComp; // current directory comp
};

#endif
