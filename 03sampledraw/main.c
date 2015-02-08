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

    SDL_Window *win = SDL_CreateWindow("Cats eye", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

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

    int count = 57;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0) {     //User requests quit
            if(e.type == SDL_QUIT) { quit = true; }
        }

        //Clear screen

        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x7F, 0x7F);

        for(int i = 0; i <= count; ++i)
        {
            SDL_RenderDrawLine(ren, i * screenWidth / 2 / count,
                               screenHeight / 2 - i * screenHeight / 2 / count,
                               screenWidth / 2 + i * screenWidth / 2 / count,
                               i * screenHeight / 2 / count);
            SDL_RenderDrawLine(ren, screenWidth / 2 + i * screenWidth / 2 / count,
                               i * screenHeight / 2 / count,
                               screenWidth  - i * screenWidth / 2 / count,
                               screenHeight / 2 + i * screenHeight / 2 / count);
            SDL_RenderDrawLine(ren, screenWidth  - i * screenWidth / 2 / count,
                               screenHeight / 2 + i * screenHeight / 2 / count,
                               screenWidth/2  - i * screenWidth / 2 / count,
                               screenHeight  - i * screenHeight / 2 / count);
            SDL_RenderDrawLine(ren, screenWidth/2  - i * screenWidth / 2 / count,
                               screenHeight  - i * screenHeight / 2 / count,
                               i * screenWidth / 2 / count,
                               screenHeight / 2 - i * screenHeight / 2 / count);
        }




        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
