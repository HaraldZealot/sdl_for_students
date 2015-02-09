#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>

const int screenWidth = 800, screenHeight = 600;

typedef struct AndrewsPoint_
{
    double *coordinates;
    int size;
} AndrewsPoint;

char *delimiters;

double transformYToScreen(double y, double scaleY);
double transformScreenToX(int scX, double scaleX);
double transformScreenToY(int scY, double scaleY);
double calcYforAndrewsPoint(AndrewsPoint point, double currentX);
double calcDerivforAndrewsPoint(AndrewsPoint point, double currentX);
double belong(double x);
double maxAbsYAndrewsPoint(AndrewsPoint point);
void drawAndrewsPoint(SDL_Renderer *ren, AndrewsPoint point, double scaleX, double scaleY);
void readData(FILE *file, AndrewsPoint **points, int *size);
void freeData(AndrewsPoint **points, int *size);

int main(int argc, char **argv)
{
    if(argc < 2 || argc > 3)
    {
        fprintf(stderr, "Invalid count of arguments (only 2 or 3 possible)\n");
        exit(1);
    }


    char *fileName;
    char delim[20] = " ";

    if(argc == 3)
    {
        if(argv[1][0] != '-' || argv[1][1] != 'd')
        {
            fprintf(stderr, "Invalid option\n");
            exit(1);
        }

        strcpy(delim, argv[1] + 2);
        fileName = argv[2];

    }
    else
        fileName = argv[1];

    delimiters = delim;

    int size = 0;
    AndrewsPoint *points = NULL;

    FILE *file = fopen(fileName, "r");

    if(!file)
    {
        fprintf(stderr, "File can't open\n");
        exit(1);
    }

    readData(file, &points, &size);

    fclose(file);

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *win = SDL_CreateWindow("Andrews diagram", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

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
    double maxY = 0.0;

    for(int i = 0; i < size; ++i)
    {
        double curY = maxAbsYAndrewsPoint(points[i]);

        if(maxY < curY)
            maxY = curY;
    }

    double scaleX = screenWidth / 2 / acos(-1.0);
    double scaleY = screenHeight / 2 / (0.1 + maxY);

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0) {     //User requests quit
            if(e.type == SDL_QUIT) { quit = true; }
        }

        SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);


        for(int i = 0; i < 1; ++i)
            drawAndrewsPoint(ren, points[i], scaleX, scaleY);

        SDL_RenderPresent(ren);
    }

    freeData(&points, &size);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

void drawAndrewsPoint(SDL_Renderer *ren, AndrewsPoint point, double scaleX, double scaleY)
{
    for(int i = 0; i < screenWidth; ++i)
    {
        double x0 = transformScreenToX(i, scaleX);
        double y0 = transformYToScreen(calcYforAndrewsPoint(point, x0), scaleY);
        int approxY = round(y0);
        double dv = calcDerivforAndrewsPoint(point, x0);
        double denominator = sqrt(1.0 + dv * dv);

        for(int j = approxY - 30; j <= approxY + 30; ++j)
        {
            double y = j;
            int alpha = 0xFF * belong((y - y0) / denominator);
            printf("%.2f %d\n",y, alpha);
            SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x7F, alpha);
            SDL_RenderDrawPoint(ren, i, j);
        }
        printf("\n");

        //,
        //(i + 2)/scale, transformYToScreen(calcYforAndrewsPoint(point, transformScreenToX(i + 2, scaleX)/scale), scaleY));
    }
}


double transformYToScreen(double y, double scaleY)
{
    return screenHeight / 2 - y * scaleY;
}

double transformScreenToX(int scX, double scaleX)
{
    return (scX - screenWidth / 2) / scaleX;
}

double transformScreenToY(int scY, double scaleY)
{
    return (screenHeight / 2 - scY) / scaleY;
}

double calcYforAndrewsPoint(AndrewsPoint point, double currentX)
{
    double result = 0.0;

    if(point.size > 0)
        result += point.coordinates[0] / sqrt(2.0);

    for(int i = 1; i < point.size; ++i)
    {
        if(i & 1)
            result += sin((i + 1) / 2 * currentX) * point.coordinates[i];
        else
            result += cos((i + 1) / 2 * currentX) * point.coordinates[i];
    }

    return result;
}

double calcDerivforAndrewsPoint(AndrewsPoint point, double currentX)
{
    double result = 0.0;

    for(int i = 1; i < point.size; ++i)
    {
        if(i & 1)
            result += ((i + 1) / 2) * cos((i + 1) / 2 * currentX) * point.coordinates[i];
        else
            result += -((i + 1) / 2) * sin((i + 1) / 2 * currentX) * point.coordinates[i];
    }

    return result;
}

double maxAbsYAndrewsPoint(AndrewsPoint point)
{
    double result = 0.0;

    for(int k = 0; k < screenWidth; ++k)
    {
        double currentX = 2.0 * acos(-1.0) * (k - screenWidth / 2) / screenWidth;
        double currentY = calcYforAndrewsPoint(point, currentX);

        if(result < fabs(currentY))
            result = fabs(currentY);
    }

    return result;
}

void countLineAndColls(FILE *file, int *lines, int *colls);

void freeData(AndrewsPoint **points, int *size)
{
    for(int i = 0; i < *size; ++i)
    {
        free((*points)[i].coordinates);
        (*points)[i].size = 0;
    }

    free(*points);
    *points = NULL;
    *size = 0;
}

void readData(FILE *file, AndrewsPoint **points, int *size)
{
    *size = 0;
    int lines, colls;
    countLineAndColls(file, &lines, &colls);
    *points = (AndrewsPoint *)malloc(lines * sizeof(AndrewsPoint));


    for(int i = 0; i < lines; ++i)
    {
        (*points)[i].coordinates = (double *)malloc(colls * sizeof(double));
        (*points)[i].size = colls;

        for(int j = 0; j < colls; ++j)
        {
            (*points)[i].coordinates[j] = 0.0;
        }

    }

    *size = lines;


    rewind(file);

    for(int i = 0; i < lines; ++i)
    {
        char buf[1024];
        fgets(buf, 1024, file);
        char *token = strtok(buf, delimiters);
        int currentColls = 0;

        while(token)
        {
            char *end;
            double val = strtod(token, &end);

            if(end != token)
            {
                (*points)[i].coordinates[currentColls] = val;
                ++currentColls;
            }


            token = strtok(NULL, delimiters);
        }
    }
}

void countLineAndColls(FILE *file, int *lines, int *colls)
{
    char buf[1024];

    *lines = 0;
    *colls = 0;

    while(!feof(file))
    {
        fgets(buf, 1024, file);
        char *token = strtok(buf, delimiters);
        int currentColls = 0;


        while(token)
        {
            char *end;
            strtod(token, &end);

            if(end != token)
                ++currentColls;

            token = strtok(NULL, delimiters);
        }

        ++(*lines);

        if(*colls < currentColls)
            *colls = currentColls;
    }
}

double belong(double x)
{
    double posX = fabs(x);
    double result;

    if(posX <= 1.0)
        result = 1.0;
    else if(posX <= 8.0)
        result = (8.0 - posX) / 7.0;
    else
        result = 0.0;

    return result;
}
