//
// Created by gregstr on 19.11.25.
//

#ifndef SPACEINVADERS_HELPERS_H
#define SPACEINVADERS_HELPERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Loads texture and sets its scaling mode to nearest, to not blur the pixels
#define LOAD_TEXTURE(Location, Path, Renderer) Location = IMG_LoadTexture(Renderer, Path); SDL_SetTextureScaleMode(Location, SDL_ScaleModeNearest);

typedef struct {
    void *data;
    int count;
    int capacity;
    size_t size;
} Vector;

// Appends an item to the end of the dynamic array implementation
#define APPEND(vector, data) do {\
    if(vector.count >= vector.capacity) {\
        if (vector.capacity == 0) vector.capacity = 8\
        vector.capacity *= 2;\
        if (vector.size == 0) vector.size = sizeof(data);\
        vector.data = realloc(vector.data, vector.capacity*vector.size);\
    } \
    vector.data[vector.count++] = data;\
    } while(0)

#define CHECK_COLLISION(x1, y1, w1, h1, x2, y2, w2, h2) \
    SDL_HasIntersection(&(SDL_Rect){x1, y1, w1, h1}, &(SDL_Rect){x2, y2, w2, h2})

static int motherShipPoints[] = {100, 50, 50, 100, 150, 100, 100, 50, 300, 100, 100, 100, 50, 150, 100, 50};
#define GET_MOTHERSHIP_VALUE(shot) motherShipPoints[shot%15]

#endif //SPACEINVADERS_HELPERS_H