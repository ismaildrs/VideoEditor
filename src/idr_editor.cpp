#include "idr_editor.hpp"

IdrEditor::IdrEditor(unsigned int width, unsigned int height, const char* name){
    initDisplay(width, height, name);
    initImGui();
}

IdrEditor::~IdrEditor(){
    closeDisplay();
    closeImGui();
}

void IdrEditor::initDisplay(unsigned int width, unsigned int height, const char* name) {
    if (!glfwInit()) {
        std::cerr << "Error initializing GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(width, height, name, nullptr, nullptr);
    if (!window) {
        std::cerr << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Error loading OpenGL function pointers with GLAD" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    window_w = width;
    window_h = height;

    videoPlayer = new VideoPlayer(width, height);
    fileManager = new FileManager(videoPlayer);
}


void IdrEditor::initImGui(){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
}

void IdrEditor::closeDisplay() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void IdrEditor::closeImGui(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool IdrEditor::windowShouldClose() {
    return glfwWindowShouldClose(window);
}


void IdrEditor::setupNewImGuiFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void IdrEditor::render(){
    setupNewImGuiFrame();

    videoPlayer->update();
    fileManager->update();

    // Render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());   

    
    // Swap Buffers
    glfwSwapBuffers(window);
}


