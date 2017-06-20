
#include <SDL2/SDL.h>

#include "WebApplication.h"
WebApplication *app = 0;
#include <emscripten.h>

void loop()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
                printf("OSGSDL. Keyup\n");
                break;
            case SDLK_DOWN:
                printf("OSGSDL. Keydown\n");
                break;
            default:
                break;
        }
        if (app)
            app->handleEvent(e);
    }
    if (app) {
        app->frame();
        //app->loadScene("box.osgt");
    }
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("OSGSDL. Could not init SDL: '%s'\n", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);
    printf("OSGSDL. init\n");
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Rendering window.
    int width = 800;
    int height = 600;
    SDL_Window* window =
        SDL_CreateWindow(
            "OSGSDL",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_OPENGL);
    if (!window)
    {
        printf("OSGSDL. Could not create window: '%s'\n", SDL_GetError());
        return 1;
    }
    SDL_GL_CreateContext(window);
    printf("OSGSDL. Created window and context\n");
    app = new WebApplication;
    app->setEmbeddedWindowSize(width, height);
    app->loadScene("box.osgt");
    emscripten_set_main_loop(loop, -1, 0);
    return 0;
}

