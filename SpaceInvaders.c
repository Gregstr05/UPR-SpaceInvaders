#include <stdlib.h>

#include "SpaceInvaders.h"

void Init(GameState *state)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    state->window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 640, SDL_WINDOW_SHOWN);
    if (state->window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (state->renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    state->bShouldClose = SDL_FALSE;
}

void Destroy(GameState *state)
{
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    SDL_Quit();
}

void Update(double deltaTime, GameState *state)
{

}

void Render(GameState *state, GameTextures *textures)
{
    SDL_Rect mediumEnemySrc = {0,0,12,12};
    SDL_Rect mediumEnemy = {0, 0, 48, 48};
    // SDL_CreateTexture(state->renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, mediumnemy.w, mediumnemy.h);
    SDL_Texture *mediumEnemyTexture = SDL_CreateTextureFromSurface(state->renderer, textures->enemies->medium);
    SDL_SetTextureScaleMode(mediumEnemyTexture, SDL_ScaleModeNearest);
    SDL_RenderCopy(state->renderer, mediumEnemyTexture, &mediumEnemySrc, &mediumEnemy);
}