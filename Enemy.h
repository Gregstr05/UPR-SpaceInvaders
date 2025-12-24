//
// Created by gregstr on 09.11.25.
//

#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include <SDL2/SDL.h>

typedef enum {
    Small,
    Medium,
    Large,
    MotherShip
} EnemyType;

typedef struct {
    EnemyType type;
    SDL_Point position;
    SDL_bool bAlive;
} Enemy;

typedef struct {
    SDL_Texture *small;
    SDL_Texture *medium;
    SDL_Texture *large;
    SDL_Texture *motherShip;
} EnemyTextures;

int LoadEnemyTextures(SDL_Renderer *renderer, EnemyTextures *enemies);
void DestroyEnemyTextures(EnemyTextures *enemies);

void InitEnemy(Enemy *enemy, EnemyType type, int posX, int posY);

void RenderEnemy(Enemy *enemy, EnemyTextures *textures, SDL_Renderer *renderer);

int GetMotherShipValue(int shots);

#endif //SPACEINVADERS_ENEMY_H
