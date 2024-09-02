#include <iostream>
#include "video_player.hpp"

int main(int argc, char* argv[])
{
    VideoPlayer video(argv[1], 2560, 1440, "Video Player");

    /* Main render loop */
    while (!video.windowShouldClose())
    {
        /* Rendering */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        video.update();
    }

    return 0;
}
