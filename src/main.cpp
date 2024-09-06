#include <iostream>
#include "idr_editor.hpp"

int main(int argc, char* argv[])
{
    /* Main render loop */
    bool paused = false;

    IdrEditor editor(2560, 1440, "VideoPlayer");

    while (!editor.windowShouldClose())
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwPollEvents();

        editor.render();

    }

    return 0;
}
