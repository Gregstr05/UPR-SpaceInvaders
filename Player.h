//
// Created by gregstr on 09.11.25.
//

#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

typedef struct {
    SDL_Point position;
    int lives;
} Player;

typedef struct {
    SDL_Texture *player;
} PlayerTextures;

void InitPlayer(Player *player);

SDL_Point MovePlayer(Player *player, int offsetX, int offsetY);
void MovePlayerTo(Player *player, SDL_Point position);

SDL_Point GetPlayerPosition(const Player *player);

void LoadPlayerTextures(SDL_Renderer *renderer, PlayerTextures *textures);
void DestroyPlayerTextures(PlayerTextures *textures);

void RenderPlayer(Player *player, PlayerTextures *textures, SDL_Renderer *renderer);

#endif //SPACEINVADERS_PLAYER_H