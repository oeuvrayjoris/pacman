#include "../include/glimac/SDLWindowManager.hpp"
#include <iostream>

#include <OpenGL/gl.h>

namespace glimac
{
    SDL_Window *window; // Declare a pointer for the window


    SDLWindowManager::SDLWindowManager(uint32_t width, uint32_t height, const char* title)
    {

        if(0 != SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << SDL_GetError() << std::endl;
            return;
        }

        SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // Create an application window with the following settings:
        window = SDL_CreateWindow(
                title,                  // window title
                SDL_WINDOWPOS_UNDEFINED,           // initial x position
                SDL_WINDOWPOS_UNDEFINED,           // initial y position
                width,                               // width, in pixels
                height,                               // height, in pixels
                SDL_WINDOW_OPENGL                  // flags - see below
        );

        if(!window) {
            std::cerr << SDL_GetError() << std::endl;
            return;
        }

        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, glContext);

        glewExperimental = GL_TRUE;
    }

    SDLWindowManager::~SDLWindowManager() {
        SDL_Quit();
    }

    bool SDLWindowManager::pollEvent(SDL_Event& e) {
        return SDL_PollEvent(&e);
    }

    bool SDLWindowManager::isKeyPressed(SDL_Keycode key) const {
        return SDL_GetKeyboardState(nullptr)[key];
    }

    // button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
    bool SDLWindowManager::isMouseButtonPressed(uint32_t button) const {
        return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
    }

    glm::ivec2 SDLWindowManager::getMousePosition() const {
        glm::ivec2 mousePos;
        SDL_GetMouseState(&mousePos.x, &mousePos.y);
        return mousePos;
    }

    void SDLWindowManager::swapBuffers() {
        SDL_GL_SwapWindow(window);
    }

    float SDLWindowManager::getTime() const {
        return 0.001f * SDL_GetTicks();
    }
}
