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

#define ANIMATED_TEXTURES(name, frames) SDL_Texture *name[frames];

#define LOAD_ANIMATED_TEXTURES(location, path, frames, ext, renderer) do{ \
        for (int i = 0; i < frames; i++) \
        {char buffer[100]; sprintf(buffer, "%s%d.%s", path, i, ext); location[i] = IMG_LoadTexture(renderer, buffer); SDL_SetTextureScaleMode(location[i], SDL_ScaleModeNearest);} \
    }while(0);

#define DESTROY_ANIMATED_TEXTURES(location, frames) do{ \
    for (int i = 0; i < frames; i++) \
    SDL_DestroyTexture(location[i]); \
    }while(0);

#endif //SPACEINVADERS_HELPERS_H