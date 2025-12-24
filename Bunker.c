//
// Created by gregstr on 24.12.25.
//

#include "Bunker.h"

void InitBunkerPart(BunkerPart *part, SDL_Point position, BunkerType type, SDL_bool bIsRight)
{
    part->type = type;
    part->health = (type==InnerCorner)?3:4;
    part->bIsRight = bIsRight;
    part->position = position;
}

void InitBunker(Bunker *bunker, SDL_Point position)
{
    for (int i = 0; i < 10; i++)
    {
        switch (i)
        {
            case 0: ASSIGN_PART(bunker, i), OuterCorner, SDL_FALSE); break;
            case 3: ASSIGN_PART(bunker, i), OuterCorner, SDL_TRUE); break;
            case 5: ASSIGN_PART(bunker, i), InnerCorner, SDL_FALSE); break;
            case 6: ASSIGN_PART(bunker, i), InnerCorner, SDL_TRUE); break;
            case 9: InitBunkerPart(&bunker->parts[9], (SDL_Point){position.x + (11 % 4 * 20), position.y + (11 / 4 * 20)}, Block, SDL_FALSE); break;
            default: ASSIGN_PART(bunker, i), Block, SDL_FALSE); break;
        }
    }
}

void LoadBunkerTextures(SDL_Renderer *renderer, BunkerTextures *bunkerTextures)
{
    LOAD_ANIMATED_TEXTURES(bunkerTextures->OuterCornerTextures, "Textures/OuterCorner", 4, "png", renderer);
    LOAD_ANIMATED_TEXTURES(bunkerTextures->InnerCornerTextures, "Textures/InnerCorner", 3, "png", renderer);
    LOAD_ANIMATED_TEXTURES(bunkerTextures->BlockTextures, "Textures/Block", 4, "png", renderer);
}

void DestroyBunkerTextures(BunkerTextures *bunkerTextures)
{
    DESTROY_ANIMATED_TEXTURES(bunkerTextures->BlockTextures, 4);
    DESTROY_ANIMATED_TEXTURES(bunkerTextures->InnerCornerTextures, 3);
    DESTROY_ANIMATED_TEXTURES(bunkerTextures->OuterCornerTextures, 4);
}

void RenderBunker(Bunker *bunker, BunkerTextures *bunkerTextures, SDL_Renderer *renderer)
{
    SDL_Rect src = {0, 0, 5, 5};
    for (int i = 0; i < 10; i++)
    {
        BunkerPart* part = &bunker->parts[i];
        if (part->health==0) continue;
        SDL_Rect dst = {part->position.x, part->position.y, 20, 20};

        switch (bunker->parts[i].type)
        {
            case OuterCorner:
                SDL_RenderCopyEx(renderer, bunkerTextures->OuterCornerTextures[part->health-1], &src, &dst, 0, NULL, (part->bIsRight)?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
                break;
            case InnerCorner:
                SDL_RenderCopyEx(renderer, bunkerTextures->InnerCornerTextures[part->health-1], &src, &dst, 0, NULL, (part->bIsRight)?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
                break;
            case Block:
                SDL_RenderCopy(renderer, bunkerTextures->BlockTextures[part->health-1], &src, &dst);
                break;
        }
    }
}
