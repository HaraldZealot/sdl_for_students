#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100,
                                       SCREEN_WIDTH, SCREEN_HEIGHT,
                                       SDL_WINDOW_SHOWN);

    if(win == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(ren == NULL)
    {
        SDL_DestroyWindow(win);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_Surface *bmp = SDL_LoadBMP("../res/hello.bmp");

    if(bmp == NULL)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);

    if(tex == NULL)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    //Now lets draw our image
    //First clear the renderer
    SDL_RenderClear(ren);
    //Draw the texture
    SDL_RenderCopy(ren, tex, NULL, NULL);
    //Update the screen

    //Have the program wait for 2000ms so we get a chance to see the screen
    bool quit = false;

    SDL_Event e;

    int x = 10, y = 10;
    int t = 0;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)       //User requests quit
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }

            if(e.type == SDL_KEYDOWN)
            {
                SDL_KeyboardEvent kEvent = e.key;

                if(kEvent.keysym.scancode == SDL_SCANCODE_A)
                {
                    x = (x - 5 + SCREEN_WIDTH) % SCREEN_WIDTH;
                }
                if(kEvent.keysym.scancode == SDL_SCANCODE_D)
                {
                    x = (x + 5 + SCREEN_WIDTH) % SCREEN_WIDTH;
                }
                if(kEvent.keysym.scancode == SDL_SCANCODE_W)
                {
                    y = (y - 5 + SCREEN_HEIGHT) % SCREEN_HEIGHT;
                }
                if(kEvent.keysym.scancode == SDL_SCANCODE_S)
                {
                    y = (y + 5 + SCREEN_HEIGHT) % SCREEN_HEIGHT;
                }
                /*if(kEvent.keysym.scancode == SDL_SCANCODE_A && kEvent.keysym.scancode == SDL_SCANCODE_W)
                {
                    x = (x - 5 + SCREEN_WIDTH) % SCREEN_WIDTH;
                    y = (y - 5 + SCREEN_HEIGHT) % SCREEN_HEIGHT;
                }*/
            }
        }

        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        x=cos(3.1415/2+0.5*sin(3.1415*t/180))*SCREEN_HEIGHT/3+SCREEN_WIDTH/2;
        y=sin(3.1415/2+0.5*sin(3.1415*t/180))*SCREEN_HEIGHT/3+SCREEN_HEIGHT/2;
        SDL_RenderDrawLine(ren, x, y, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        aacircleRGBA(ren,x,y,20,0xFF,0x7F,0x00,0xFF);
        SDL_RenderPresent(ren);
        ++t;
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
