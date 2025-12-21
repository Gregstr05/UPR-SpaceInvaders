//
// Created by gregstr on 09.11.25.
//

#include "Player.h"

#include <SDL2/SDL_image.h>

#include "Helpers.h"

void InitPlayer(Player *player)
{
    player->position = (SDL_Point){200, 550};
    player->lives = 3;
}

SDL_Point MovePlayer(Player *player, int offsetX, int offsetY)
{
    player->position.x += offsetX;
    player->position.y += offsetY;
    return player->position;
}

void MovePlayerTo(Player *player, SDL_Point position)
{
    player->position = position;
}

SDL_Point GetPlayerPosition(const Player *player)
{
    return player->position;
}

void LoadPlayerTextures(SDL_Renderer *renderer, PlayerTextures *textures)
{
    LOAD_TEXTURE(textures->player, "Textures/Player.png", renderer);
}

void DestroyPlayerTextures(PlayerTextures *textures)
{
    SDL_DestroyTexture(textures->player);
    textures->player = NULL;
}

void RenderPlayer(Player *player, PlayerTextures *textures, SDL_Renderer *renderer)
{
    SDL_Rect src = {0,0,13,12};
    SDL_Rect dst = {player->position.x, player->position.y, 26, 24};
    SDL_RenderCopy(renderer, textures->player, &src, &dst);
}

void Fire(Player *player)
{
    printf("Fire at: x: %d\n", player->position.x);
}
