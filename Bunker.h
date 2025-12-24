//
// Created by gregstr on 24.12.25.
//

#ifndef SPACEINVADERS_BUNKER_H
#define SPACEINVADERS_BUNKER_H
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>

#include "Helpers.h"

#define ASSIGN_PART(bunker, iterator) InitBunkerPart(&bunker->parts[iterator], (SDL_Point){position.x+(iterator%4*20), position.y+(iterator/4*20)}

typedef enum {
    OuterCorner,
    InnerCorner,
    Block
} BunkerType;

typedef struct {
    BunkerType type;
    SDL_Point position;
    int health;
    SDL_bool bIsRight;
} BunkerPart;

typedef struct {
    //  /##\ - 4
    //  #/\# - 4
    //  #  # - 2
    // 4+4+2=10
    BunkerPart parts[10];
    SDL_Point position;
    SDL_bool bAlive;
} Bunker;

typedef struct {
    ANIMATED_TEXTURES(OuterCornerTextures, 4);
    ANIMATED_TEXTURES(InnerCornerTextures, 3);
    ANIMATED_TEXTURES(BlockTextures, 4);
} BunkerTextures;

void InitBunkerPart(BunkerPart *part, SDL_Point position, BunkerType type, SDL_bool bIsRight);
void InitBunker(Bunker *bunker, SDL_Point position);

void LoadBunkerTextures(SDL_Renderer *renderer, BunkerTextures *bunkerTextures);
void DestroyBunkerTextures(BunkerTextures *bunkerTextures);

void RenderBunker(Bunker *bunker, BunkerTextures *bunkerTextures, SDL_Renderer *renderer);

#endif