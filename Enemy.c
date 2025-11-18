#include "Enemy.h"

#include <SDL2/SDL_image.h>

int LoadEnemyTextures(SDL_Renderer *renderer, EnemyTextures **enemies)
{
    (*enemies)->large = IMG_LoadTexture(renderer, "Textures/Large.png");
    (*enemies)->medium = IMG_LoadTexture(renderer, "Textures/Medium.png");
    (*enemies)->small = IMG_LoadTexture(renderer, "Textures/Small.png");
    return 0;
}

void DestroyEnemyTextures(SDL_Renderer *renderer, EnemyTextures **enemies)
{
    SDL_DestroyTexture((*enemies)->large);
    (*enemies)->large = NULL;
    SDL_DestroyTexture((*enemies)->medium);
    (*enemies)->medium = NULL;
    SDL_DestroyTexture((*enemies)->small);
    (*enemies)->small = NULL;
}