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

    int m;

    int phi =0;
    double PI=acos(-1.0);

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0) {     //User requests quit
            if(e.type == SDL_QUIT) { quit = true; }
            if(e.type == SDL_KEYDOWN)
            {
                SDL_KeyboardEvent kEvent = e.key;

                if(kEvent.keysym.scancode == SDL_SCANCODE_A)
                {
                    ++m;
                }

                if(kEvent.keysym.scancode == SDL_SCANCODE_D)
                {
                    --m;
                }
            }
        }

        //Clear screen

        //SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);


        double dt = PI/ 1024.0;



        for(int i = 0; i <= count; ++i)
        {
            SDL_SetRenderDrawColor(ren, i&0xFF, (i&0xFF00)>>8, 0x7F, 0x7F);
            double t = i * acos(-1) / 1024.0;
            SDL_RenderDrawLine(ren,
                               screenWidth / 2 + 0.375 * screenWidth * cos(m*t+PI*phi/180.0),
                               screenHeight / 2 - 0.375 * screenHeight * sin(2*t+PI*phi/180.0),
                               screenWidth / 2 + 0.375 * screenWidth * cos(m*(t + dt)+PI*phi/180.0),
                               screenHeight / 2 - 0.375 * screenHeight * sin(2*(t + dt)+PI*phi/180.0));
        }

        SDL_RenderPresent(ren);
        ++phi;
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
