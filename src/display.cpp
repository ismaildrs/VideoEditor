#include "../include/display.hpp"

Display::Display(unsigned int width, unsigned int height, const char* name){
    if(!glfwInit()){
        #ifdef TEST_VERSION
            std::cerr << "Error initializing GLFW";
        #endif
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(width, height, name, nullptr, nullptr);

    if(!window){
        #ifdef TEST_VERSION
            std::cerr << "Error initializing GLFW";
        #endif
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        #ifdef TEST_VERSION
            std::cerr << "Error Loading OpenGL function pointers with GLAD";
        #endif
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

Display::~Display(){
    glfwTerminate();
}

int Display::windowShouldClose(){
    return glfwWindowShouldClose(window);
}

void Display::update(){

    glfwSwapBuffers(window);

    glfwPollEvents();

}