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

void InitProjectile(Projectile *projectile, SDL_Point position, ProjectileType type)
{
    projectile->x = position.x;
    projectile->y = position.y;
    projectile->type = type;
    projectile->velocity = (type == EnemyProjectile)?4:-4;
}

void UpdateProjectile(Projectile *projectile, double deltaTime) {
    if (projectile->type == PlayerProjectile) {
        projectile->y -= (int)(projectile->velocity * deltaTime);
    } else {
        projectile->y += (int)(projectile->velocity * deltaTime);
    }
}

void RenderProjectile(Projectile *projectile, ProjectileTextures *textures, SDL_Renderer *renderer)
{
    SDL_Rect src = {0,0,8,12};
    SDL_Rect dst = {projectile->x, projectile->y, 16, 24};
    SDL_RenderCopy(renderer, textures->player, &src, &dst);
}
