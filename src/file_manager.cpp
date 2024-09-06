#include "file_manager.hpp"

FileManager::FileManager(VideoPlayer* video){
    this->video = video;
    // std::filesystem::path newPath = "/home/ismaildrs/Downloads";
    // std::filesystem::current_path(newPath);
    currentDir = std::filesystem::current_path();
    setCurrentDirComp();
}

void FileManager::update() {
    setCurrentDirComp();
    
    if (ImGui::Begin(currentDir.filename().string().c_str(), nullptr, ImGuiWindowFlags_NoResize)) {
        ImVec2 position(0, 0);
        ImGui::SetWindowPos(position);


        ImVec4 customColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);  // RGBA for red

        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, customColor);

        // Display a ".." to go to the parent directory
        if (currentDir != currentDir.root_path()) {
            if (ImGui::Selectable("..")) {
                currentDir = currentDir.parent_path();
                setCurrentDirComp();
            }
        }

        // Display directories
        for (const auto& elem : currentDirComp.dirs) {
            std::string name = "\U0001F4C1 " + elem.filename().string();
            if (ImGui::Selectable(name.c_str()) ){
                currentDir = elem;  // Change to the clicked directory
                setCurrentDirComp(); // Update the directory contents
                ImGui::PopStyleColor();     
                ImGui::End();
                return;
            }
        }

        ImGui::PopStyleColor();

        customColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // RGBA for red

        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, customColor);      

        // Display files
        for (const auto& file : currentDirComp.files) {
            if (ImGui::Selectable(file.c_str())) {
                std::string filePath = currentDir.string() + "/" + file.c_str();
                video->setFilePath(filePath.c_str());
                ImGui::PopStyleColor();
                ImGui::End();
                return;
            }
        }

        ImGui::PopStyleColor();

        ImVec2 size((ImGui::GetIO().DisplaySize.x - 1000) * 0.5f, 600);
        ImGui::SetWindowSize(size);
    }
    ImGui::End();
}


void FileManager::setCurrentDirComp() {
    currentDirComp.dirs.clear();
    currentDirComp.files.clear();

    for (auto& entry : std::filesystem::directory_iterator(currentDir)) {
        if (entry.is_directory()) {
            currentDirComp.dirs.push_back(entry.path());
        } else {
            currentDirComp.files.push_back(entry.path().filename().string());
        }
    }
}