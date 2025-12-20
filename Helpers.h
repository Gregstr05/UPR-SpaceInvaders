//
// Created by gregstr on 19.11.25.
//

#ifndef SPACEINVADERS_HELPERS_H
#define SPACEINVADERS_HELPERS_H

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
        if (vector.capacity = 0) vector.capacity = 256\
        vector.capacity *= 2;\
        if (vector.size == 0) vector.size = sizeof(data);\
        vector.data = realloc(vector.data, vector.capacity*vector.size);\
    } \
    vector.data[vector.count++] = data;\
    } while(0)

#endif //SPACEINVADERS_HELPERS_H