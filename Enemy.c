#include "Enemy.h"

#include <SDL2/SDL_image.h>

#include "Helpers.h"
#include "SpaceInvaders.h"

int LoadEnemyTextures(SDL_Renderer *renderer, EnemyTextures *enemies)
{
    LOAD_TEXTURE(enemies->large, "Textures/Large.png", renderer);
    LOAD_TEXTURE(enemies->medium, "Textures/Medium.png", renderer);
    LOAD_TEXTURE(enemies->small, "Textures/Small.png", renderer);
    return 0;
}

void DestroyEnemyTextures(SDL_Renderer *renderer, EnemyTextures *enemies)
{
    SDL_DestroyTexture(enemies->large);
    enemies->large = NULL;
    SDL_DestroyTexture(enemies->medium);
    enemies->medium = NULL;
    SDL_DestroyTexture(enemies->small);
    enemies->small = NULL;
}

void InitEnemy(Enemy *enemy, EnemyType type, int posX, int posY)
{
    enemy->type = type;
    enemy->bAlive = SDL_TRUE;
    enemy->poxX = posX;
    enemy->poxY = posY;
}

void RenderEnemy(Enemy *enemy, EnemyTextures *textures, SDL_Renderer *renderer)
{
    if (!enemy->bAlive)
        return;
    SDL_Rect src = {0,0,12,12};
    SDL_Rect dst = {enemy->poxX, enemy->poxY, 48, 48};
    switch (enemy->type)
    {
        case Small: SDL_RenderCopy(renderer, textures->small, &src, &dst); break;
        case Medium: SDL_RenderCopy(renderer, textures->medium, &src, &dst); break;
        case Large: SDL_RenderCopy(renderer, textures->large, &src, &dst); break;
    }
}