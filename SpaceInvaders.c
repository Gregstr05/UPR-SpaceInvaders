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

void Update(double deltaTime, GameState *state, GameData *gameData)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: state->bShouldClose = SDL_TRUE; break;
            case SDL_KEYDOWN: switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE: state->bShouldClose = SDL_TRUE; break;
            }
        }
    }
}

void Render(GameState *state, GameTextures *textures, GameData *gameData)
{
    SDL_Rect mediumEnemySrc = {0,0,12,12};
    SDL_Rect mediumEnemy = {0, 0, 48, 48};
    SDL_RenderCopy(state->renderer, textures->enemies->medium, &mediumEnemySrc, &mediumEnemy);
}