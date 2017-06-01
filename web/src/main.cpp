
#include <SDL2/SDL.h>

#define OSGSDL_PLATFORM_WEB

#ifndef OSGSDL_PLATFORM_WEB
    #include "Application.h"
    Application *app = 0;
    bool done = false;
#else // OSGSDL_PLATFORM_WEB
    #include "WebApplication.h"
    WebApplication *app = 0;
    #include <emscripten.h>
#endif // OSGSDL_PLATFORM_WEB

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
#ifndef OSGSDL_PLATFORM_WEB
        switch (e.type)
        {
            /*
             * TODO: Handle resize event.
            case SDL_VIDEORESIZE:
                SDL_SetVideoMode(e.resize.w, e.resize.h, bitDepth, SDL_OPENGL | SDL_RESIZABLE);
                gw->resized(0, 0, event.resize.w, event.resize.h );
                break;
            */
            case SDL_KEYUP:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                /*
                 * TODO: Handle resizing.
                if (event.key.keysym.sym=='f')
                {
                    SDL_WM_ToggleFullScreen(screen);
                    gw->resized(0, 0, screen->w, screen->h );
                }
                */
                break;
            case SDL_QUIT:
                done = true;
                break;
            default:
                break;
        }
#endif // OSGSDL_PLATFORM_WEB
    }
    if (app) {
        app->frame();
#ifdef OSGSDL_PLATFORM_WEB
        app->loadScene("box.osgt");
#endif
    }
}

int main(int argc, char *argv[])
{
#ifndef OSGSDL_PLATFORM_WEB
    if (argc < 2)
    {
        printf("%s: requires filename argument.\n", argv[0]);
        return 1;
    }
#endif // OSGSDL_PLATFORM_WEB
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
#ifndef OSGSDL_PLATFORM_WEB
    app = new Application;
    app->setEmbeddedWindowSize(width, height);
    app->loadScene(argv[1]);
    // Main loop.
    while (!done)
    {
        loop();
        SDL_GL_SwapWindow(window);
    }
    delete app;
#else // OSGSDL_PLATFORM_WEB
    app = new WebApplication;
    app->setEmbeddedWindowSize(width, height);
    //app->loadScene("box.osgt");
    emscripten_set_main_loop(loop, -1, 0);
#endif // OSGSDL_PLATFORM_WEB
    return 0;
}

