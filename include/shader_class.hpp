#ifndef SHADER_CLASS
#define SHADER_CLASS

#include "constants.hpp"
#include "glad/glad.h"
#include <fstream>
#include <iostream>
#include <string> 
#include <sstream>

class Shader{
    unsigned int ID;
public:
    Shader();
    void use();
    void setUniform(const std::string &name, bool value) const;
    void setUniform(const std::string &name, int unit) const;
    void setUniform(const std::string &name, float value) const;
};

#endif