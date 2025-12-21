#include <stdlib.h>

#include "SpaceInvaders.h"

void Init(GameState *state)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
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
    int totalGridWidth = (11 * 24) + ((11 - 1) * 8);
    int startX = ((SCREEN_WIDTH - totalGridWidth) / 2) - 44;

    int currentEnemyIndex = 0;
    for (int row = 0; row < NUM_ENEMIES/11; row++)
    {
        EnemyType type;
        if (row == 0) {
            type = Small;
        } else if (row == 1 || row == 2) {
            type = Medium;
        } else { // rows 3 and 4
            type = Large;
        }

        for (int col = 0; col < 11; col++)
        {
            int posX = startX + (col * (24 + 20));
            int posY = 80 + (row * (24 + 8));

            InitEnemy(&data->enemies[currentEnemyIndex], type, posX, posY);
            currentEnemyIndex++;
        }
    }

    InitPlayer(&data->player);
}

void LoadTextures(SDL_Renderer *renderer, GameTextures *textures)
{
    LoadEnemyTextures(renderer, &textures->enemies);
    LoadPlayerTextures(renderer, &textures->player);
    LoadProjectileTextures(renderer, &textures->projectiles);
}

void DestroyTextures(GameTextures *textures)
{
    DestroyEnemyTextures(&textures->enemies);
    DestroyPlayerTextures(&textures->player);
    DestroyProjectileTextures(&textures->projectiles);
}

void Destroy(GameState *state)
{
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    IMG_Quit();
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
                case SDLK_SPACE: Fire(&gameData->player); break;
                default: break;
            }
            default: break;
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    float moveSpeed = 200.0f; // pixels per second

    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
    {
        int newX = gameData->player.position.x - (int)(moveSpeed * deltaTime);
        if (newX < 0) newX = 0;
        gameData->player.position.x = newX;
    }

    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
    {
        int newX = gameData->player.position.x + (int)(moveSpeed * deltaTime);
        // Clamp to screen bounds (player width is 52 pixels)
        if (newX > SCREEN_WIDTH - 52) newX = SCREEN_WIDTH - 52;
        gameData->player.position.x = newX;
    }

}

void Render(GameState *state, GameTextures *textures, GameData *gameData)
{
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        RenderEnemy(&gameData->enemies[i], &textures->enemies, state->renderer);
    }

    RenderPlayer(&gameData->player, &textures->player, state->renderer);
}