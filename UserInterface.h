#ifndef  SPACEINVADERS_USERINTERFACE_H
#define SPACEINVADERS_USERINTERFACE_H
#include "SpaceInvaders.h"

void RenderUI(SDL_Renderer *renderer, GameData *data, GameTextures *textures);

void RenderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y);

#endif