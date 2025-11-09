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

#endif //SPACEINVADERS_ENEMY_H