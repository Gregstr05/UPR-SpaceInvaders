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
    int poxX;
    int poxY;
    SDL_bool bAlive;
} Enemy;

typedef struct {
    SDL_Surface *small;
    SDL_Surface *medium;
    SDL_Surface *large;
} EnemyTextures;

int LoadEnemyTextures(EnemyTextures **enemies);

#endif //SPACEINVADERS_ENEMY_H