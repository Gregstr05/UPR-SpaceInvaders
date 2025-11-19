#include "Enemy.h"

#include <SDL2/SDL_image.h>

#include "Helpers.h"

int LoadEnemyTextures(SDL_Renderer *renderer, EnemyTextures **enemies)
{
    LOAD_TEXTURE((*enemies)->large, "Textures/Large.png", renderer);
    LOAD_TEXTURE((*enemies)->medium, "Textures/Medium.png", renderer);
    LOAD_TEXTURE((*enemies)->small, "Textures/Small.png", renderer);
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