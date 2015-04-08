#include "sdlwrapper.h"
#include <exception>

using namespace std;

SDLWrapper::SDLWrapper()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        throw exception();
}

SDLWrapper::~SDLWrapper()
{
    SDL_Quit();
}



SDLWindowWrapper::SDLWindowWrapper(const char *title, int x, int y,
                                   int w, int h, Uint32 flags):
    win_(nullptr)
{
    win_ = SDL_CreateWindow(title, x, y, w, h, flags);
    if(win_ == nullptr)
        throw exception();
}

SDLWindowWrapper::~SDLWindowWrapper()
{
    SDL_DestroyWindow(win_);
}


SDLRendererWrapper::SDLRendererWrapper(SDL_Window *win, int index, Uint32 flags):
    ren_(nullptr)
{
    ren_ = SDL_CreateRenderer(win, index, flags);
    if(ren_ == nullptr)
        throw exception();
}

SDLRendererWrapper::~SDLRendererWrapper()
{
    SDL_DestroyRenderer(ren_);
}
