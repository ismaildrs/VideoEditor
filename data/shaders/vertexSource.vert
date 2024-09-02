#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aCoord;

out vec3 ourColor;
out vec2 textCoord;
  
void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    textCoord = aCoord;
}