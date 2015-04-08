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
};

#endif // SDLWRAPPER_H
