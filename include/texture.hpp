#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "stb_image.h"
#include "glad/glad.h"
#include "constants.hpp"
#include <iostream>
#include <cstddef> // For size_t

class Texture {
public:
    Texture();
    ~Texture();

    unsigned int getTextureId(){
        return m_texture;
    }

    void setTexture(const unsigned char* data, int width, int height);
    void bind(unsigned int unit = 0) const;

    unsigned int m_texture = 0; // Pointer to dynamically allocated array of texture IDs
private:
};

#endif // TEXTURE_HPP
