#include <stdlib.h>

#include "SpaceInvaders.h"

void Init(GameState *state)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    state->window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void InitGameData(GameData *data)
{
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        InitEnemy(&data->Enemies[i], Large, (i+1)*(SCREEN_WIDTH/(8)), (i/8+1)*(SCREEN_HEIGHT/(11*12)));
    }
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
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT: state->bShouldClose = SDL_TRUE; break;
        case SDL_KEYDOWN: switch (event.key.keysym.sym)
        {
            case SDLK_ESCAPE: state->bShouldClose = SDL_TRUE; break;
            default: break;
        }
        default: break;
    }

}

void Render(GameState *state, GameTextures *textures, GameData *gameData)
{
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        RenderEnemy(&gameData->Enemies[i], &textures->enemies, state->renderer);
    }
}