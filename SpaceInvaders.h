
#ifndef SPACEINVADERS_SPACEINVADERS_H
#define SPACEINVADERS_SPACEINVADERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"

// Number of enemies (Lines * Columns + 1 for mothership)
#define NUM_ENEMIES (5*11+1)

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_bool bShouldClose;
} GameState;

typedef struct {
    Player player;
    Enemy enemies[NUM_ENEMIES];

    Projectile projectiles[MAX_PROJECTILES];
    int numActiveProjectiles;

    int alienDirection; // 1 for right, -1 for left
    float alienMoveTimer;
    float alienMoveInterval;
} GameData;

typedef struct {
    EnemyTextures enemies;
    PlayerTextures player;
    ProjectileTextures projectiles;
} GameTextures;

/**
 * Initializes SDL and stores important pointers in the GameState reference
 * @param state GameState reference
 */
void Init(GameState *state);

void InitGameData(GameData *data);

void LoadTextures(SDL_Renderer *renderer, GameTextures *textures);
void DestroyTextures(GameTextures *textures);

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
void Update(double deltaTime, GameState *state, GameData *gameData);

/**
 * Gets called every frame after Update() and renders based on game data
 * @param state GameState reference
 */
void Render(GameState *state, GameTextures *textures, GameData *gameData);

#endif //SPACEINVADERS_SPACEINVADERS_H