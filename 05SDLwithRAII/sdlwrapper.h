#ifndef SDLWRAPPER_H
#define SDLWRAPPER_H

#include <SDL2/SDL.h>


class SDLWrapper
{
public:
    SDLWrapper();
    ~SDLWrapper();
};

class SDLWindowWrapper
{
public:
    SDLWindowWrapper(const char *title, int x, int y, int w, int h, Uint32 flags);
    ~SDLWindowWrapper();
    SDL_Window *win() const { return win_;}
private:
    SDL_Window *win_;
};

class SDLRendererWrapper
{
public:
    SDLRendererWrapper(SDL_Window *win, int index, Uint32 flags);
    ~SDLRendererWrapper();
    SDL_Renderer *ren() {return ren_;}
private:
    SDL_Renderer *ren_;

};

#endif // SDLWRAPPER_H
