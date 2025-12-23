#include "Enemy.h"

#include <SDL2/SDL_image.h>

#include "Helpers.h"
#include "SpaceInvaders.h"

int LoadEnemyTextures(SDL_Renderer *renderer, EnemyTextures *enemies)
{
    LOAD_TEXTURE(enemies->large, "Textures/Large.png", renderer);
    LOAD_TEXTURE(enemies->medium, "Textures/Medium.png", renderer);
    LOAD_TEXTURE(enemies->small, "Textures/Small.png", renderer);
    LOAD_TEXTURE(enemies->motherShip, "Textures/MotherShip.png", renderer);
    return 0;
}

void DestroyEnemyTextures(EnemyTextures *enemies)
{
    SDL_DestroyTexture(enemies->large);
    enemies->large = NULL;
    SDL_DestroyTexture(enemies->medium);
    enemies->medium = NULL;
    SDL_DestroyTexture(enemies->small);
    enemies->small = NULL;
    SDL_DestroyTexture(enemies->motherShip);
    enemies->motherShip = NULL;
}

void InitEnemy(Enemy *enemy, EnemyType type, int posX, int posY)
{
    enemy->type = type;
    enemy->bAlive = SDL_TRUE;
    enemy->position.x = posX;
    enemy->position.y = posY;
}

void RenderEnemy(Enemy *enemy, EnemyTextures *textures, SDL_Renderer *renderer)
{
    if (!enemy->bAlive)
        return;
    SDL_Rect src = {0,0,12,12};
    SDL_Rect dst = {enemy->position.x, enemy->position.y, 24, 24};
    switch (enemy->type)
    {
        case Small: SDL_RenderCopy(renderer, textures->small, &src, &dst); break;
        case Medium: SDL_RenderCopy(renderer, textures->medium, &src, &dst); break;
        case Large: SDL_RenderCopy(renderer, textures->large, &src, &dst); break;
        case MotherShip:
            SDL_Rect src2 = {0,0,16,7};
            SDL_Rect dst2 = {enemy->position.x, enemy->position.y, 32, 14};
            SDL_RenderCopy(renderer, textures->motherShip, &src2, &dst2); break;
        default: break;
    }
}