//
// Created by gregstr on 20.12.25.
//

#include "Projectile.h"

#include <SDL2/SDL_image.h>

#include "Helpers.h"

int LoadProjectileTextures(SDL_Renderer *renderer, ProjectileTextures *projectileTextures)
{
    LOAD_TEXTURE(projectileTextures->enemy, "Textures/EnemyProjectile.png", renderer)
}

void DestroyProjectileTextures(ProjectileTextures *projectileTextures)
{
    SDL_DestroyTexture(projectileTextures->player);
}

void InitProjectile(Projectile *projectile, SDL_Point position)
{
    projectile->x = position.x;
    projectile->y = position.y;
    projectile->type = EnemyProjectile;
    projectile->velocity = 8;
}

void RenderProjectile(Projectile *projectile, ProjectileTextures *textures, SDL_Renderer *renderer)
{
    SDL_Rect src = {0,0,8,12};
    SDL_Rect dst = {projectile->x, projectile->y, 16, 24};
    SDL_RenderCopy(renderer, textures->player, &src, &dst);
}
