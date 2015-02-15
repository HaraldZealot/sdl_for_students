#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int screenWidth = 640, screenHeight = 480;

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *win = SDL_CreateWindow("Lisaju", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    if(win == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(ren == NULL) {
        SDL_DestroyWindow(win);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }


    bool quit = false;

    SDL_Event e;

    int count = 2048;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0) {     //User requests quit
            if(e.type == SDL_QUIT) { quit = true; }
        }

        //Clear screen

        //SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x7F, 0x7F);

        double dt = acos(-1) / 1024.0;

        for(int i = 0; i <= count; ++i)
        {
            double t = i * acos(-1) / 1024.0;
            SDL_RenderDrawLine(ren,
                               screenWidth / 2 + 0.375 * screenWidth * cos(3*t),
                               screenHeight / 2 - 0.375 * screenHeight * sin(2*t),
                               screenWidth / 2 + 0.375 * screenWidth * cos(3*(t + dt)),
                               screenHeight / 2 - 0.375 * screenHeight * sin(2*(t + dt)));
        }

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
