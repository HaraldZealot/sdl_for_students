#include "sdlwrapper.h"
#include <exception>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

class SDLException: public exception
{
public:
    SDLException(char *message)
    {
        strncpy(this->message, message, 512);
    }

    const char *what() const noexcept override
    {
        return message;
    }

private:
    char message[512];
};


SDLWrapper::SDLWrapper()
{
    clog<<"ctor SDLWrapper\n";
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        char message[512];
        sprintf(message, "in SDL_Init %s", SDL_GetError());
        throw SDLException(message);
    }
}

SDLWrapper::~SDLWrapper()
{
    SDL_Quit();
    clog<<"dtor SDLWrapper\n";
}



SDLWindowWrapper::SDLWindowWrapper(const char *title, int x, int y,
                                   int w, int h, Uint32 flags):
    win_(nullptr)
{
    clog<<"ctor SDLWindowWrapper\n";
    win_ = SDL_CreateWindow(title, x, y, w, h, flags);
    if(win_ == nullptr)
    {
        char message[512];
        sprintf(message, "in SDL_CreateWindow %s", SDL_GetError());
        throw SDLException(message);
    }
}

SDLWindowWrapper::~SDLWindowWrapper()
{
    SDL_DestroyWindow(win_);
    clog<<"dtor SDLWindowWrapper\n";
}


SDLRendererWrapper::SDLRendererWrapper(SDL_Window *win, int index, Uint32 flags):
    ren_(nullptr)
{
    clog<<"ctor SDLRendererWrapper\n";
    ren_ = SDL_CreateRenderer(win, index, flags);
    if(ren_ == nullptr)
    {
        char message[512];
        sprintf(message, "in SDL_CreateRenderer %s", SDL_GetError());
        throw SDLException(message);
    }
}

SDLRendererWrapper::~SDLRendererWrapper()
{
    SDL_DestroyRenderer(ren_);
    clog<<"dtor SDLRendererWrapper\n";
}
