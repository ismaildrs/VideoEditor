#ifndef DATA_HPP
#define DATA_HPP

#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "constants.hpp"

class Display{
public:
    Display(unsigned int width, unsigned int height, const char* name);
    ~Display();
    void update();
    int windowShouldClose();
private:
    GLFWwindow* window;
};

#endif