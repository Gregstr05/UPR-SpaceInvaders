//
// Created by gregstr on 09.11.25.
//

#ifndef SPACEINVADERS_SPACEINVADERS_H
#define SPACEINVADERS_SPACEINVADERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
}GameState;

void Init();

void Update(double deltaTime, GameState *state);
void Render(GameState *state);

#endif //SPACEINVADERS_SPACEINVADERS_H