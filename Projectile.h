//
// Created by gregstr on 20.12.25.
//

#ifndef SPACEINVADERS_PROJECTILE_H
#define SPACEINVADERS_PROJECTILE_H
#include <SDL2/SDL_render.h>

typedef enum {
    PlayerProjectile,
    EnemyProjectile
} ProjectileType;

typedef struct {
    ProjectileType type;
    int x, y;
    int velocity;
} Projectile;

typedef struct {
    SDL_Texture* player;
    SDL_Texture* enemy;
} ProjectileTextures;

int LoadProjectileTextures(SDL_Renderer *renderer, ProjectileTextures *projectileTextures);
void DestroyProjectileTextures(ProjectileTextures *projectileTextures);

#endif