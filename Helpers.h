//
// Created by gregstr on 19.11.25.
//

#ifndef SPACEINVADERS_HELPERS_H
#define SPACEINVADERS_HELPERS_H

#define LOAD_TEXTURE(Location, Path, Renderer) Location = IMG_LoadTexture(Renderer, Path); SDL_SetTextureScaleMode(Location, SDL_ScaleModeNearest);

#endif //SPACEINVADERS_HELPERS_H