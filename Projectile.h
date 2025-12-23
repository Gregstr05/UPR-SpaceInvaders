//
// Created by gregstr on 20.12.25.
//

#ifndef SPACEINVADERS_PROJECTILE_H
#define SPACEINVADERS_PROJECTILE_H
#include <SDL2/SDL_render.h>

#define MAX_PROJECTILES 32

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

void LoadProjectileTextures(SDL_Renderer *renderer, ProjectileTextures *projectileTextures);
void DestroyProjectileTextures(ProjectileTextures *projectileTextures);

void InitProjectile(Projectile *projectile, SDL_Point position, ProjectileType type);

void UpdateProjectile(Projectile *projectile, double deltaTime);

void RenderProjectile(Projectile *projectile, ProjectileTextures *textures, SDL_Renderer *renderer);

#endif
