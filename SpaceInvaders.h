
#ifndef SPACEINVADERS_SPACEINVADERS_H
#define SPACEINVADERS_SPACEINVADERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Number of enemies (Lines * Columns + 1 for mothership)
#define NUM_ENEMIES (5*11+1)

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_bool bShouldClose;
} GameState;

typedef struct {
    int posX;
    int posY;
    int Lifes;
} Player;

typedef enum {
    Small,
    Medium,
    Large,
    MotherShip
} EnemyType;

typedef struct {
    EnemyType type;
    int poxX;
    int poxY;
    SDL_bool bAlive;
} Enemy;

typedef struct {
    Player *player;
    Enemy Enemies[NUM_ENEMIES];
} GameData;

/**
 * Initializes SDL and stores important pointers in the GameState reference
 * @param state GameState reference
 */
void Init(GameState *state);

/**
 * Cleans up SDL
 * @param state GameState reference
 */
void Destroy(GameState *state);

/**
 * Gets called every frame and updates game values
 * @param deltaTime Time difference between this and previous frame
 * @param state GameState reference
 */
void Update(double deltaTime, GameState *state);

/**
 * Gets called every frame after Update() and renders based on game data
 * @param state GameState reference
 */
void Render(GameState *state);

#endif //SPACEINVADERS_SPACEINVADERS_H