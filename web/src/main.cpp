
#include <emscripten.h>
#include <SDL2/SDL.h>

#include "main.h"

// We use app global variable in loop() function.
Application *app = 0;

// Stand alone function that is called by Emscripten to run the app.
void loop()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (app)
        {
            app->handleEvent(e);
        }
    }
    if (app)
    {
        app->frame();
    }
}

int main(int argc, char *argv[])
{
    // Make sure SDL is working.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("OSGWeb. Could not init SDL: '%s'\n", SDL_GetError());
        return 1;
    }
    // Clean SDL up at exit.
    atexit(SDL_Quit);
    // Configure rendering context.
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Create rendering window.
    int width = 800;
    int height = 600;
    SDL_Window* window =
        SDL_CreateWindow(
            "OSGWeb",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_OPENGL);
    if (!window)
    {
        printf("OSGWeb. Could not create window: '%s'\n", SDL_GetError());
        return 1;
    }
    SDL_GL_CreateContext(window);
    // Create application.
    app = new Application;
    app->setupWindow(width, height);
    app->loadScene("res/box.osgt");
    // Render asynchronously.
    emscripten_set_main_loop(loop, -1, 0);
    return 0;
}

