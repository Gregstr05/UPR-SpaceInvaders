
#ifndef SPACEINVADERS_SPACEINVADERS_H
#define SPACEINVADERS_SPACEINVADERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Bunker.h"
#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"

// Number of enemies (Lines * Columns + 1 for mothership)
#define NUM_ENEMIES (5*11+1)

#define UFO_INDEX NUM_ENEMIES-1

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef enum {
    PHASE_MENU,
    PHASE_PLAYING,
    PHASE_GAME_OVER
} GamePhase;

typedef struct {
    char name[7];
    int score;
} HighScore;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_bool bShouldClose;
} GameState;

typedef struct {
    Player player;
    int score;
    int shots;

    // Should not be accesed anywhere but in game over phase
    char playerName[7];
    int nameCharIndex;

    HighScore highScores[5];
    int numHighScores;

    GamePhase phase;

    Enemy enemies[NUM_ENEMIES];
    SDL_bool bAlive;

    Bunker bunkers[4];

    Projectile playerProjectile;
    SDL_bool bPlayerProjectileActive;

    Projectile enemyProjectiles[MAX_PROJECTILES];
    int numActiveEnemyProjectiles;

    int alienDirection; // 1 for right, -1 for left
    float alienMoveTimer;
    float alienMoveInterval;

    float alienFireTimer;
    float alienFireInterval;

    float motherShipSpawnTimer;
    float motherShipSpawnInterval;
    int motherShipDirection;
} GameData;

typedef struct {
    EnemyTextures enemies;
    PlayerTextures player;
    ProjectileTextures projectiles;
    BunkerTextures bunkers;
    TTF_Font *font;
} GameTextures;

/**
 * Initializes SDL and stores important pointers in the GameState reference
 * @param state GameState reference
 */
void Init(GameState *state);

void InitGameData(GameData *data);
void SpawnEnemies(GameData *gameData);

void LoadTextures(SDL_Renderer *renderer, GameTextures *textures);
void DestroyTextures(GameTextures *textures);

void SaveScore(const char *name, int score);
void LoadHighScores(GameData *data);

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

void UpdateGamePlay(double deltaTime, GameData *gameData);
void UpdateGameOver(double deltaTime, GameState *state, GameData *gameData);
void UpdateMenu(double deltaTime, GameState *state, GameData *gameData);

/**
 * Gets called every frame after Update() and renders based on game data
 * @param state GameState reference
 */
void Render(GameState *state, GameTextures *textures, GameData *gameData);

void RenderUI(SDL_Renderer *renderer, GameData *data, GameTextures *textures);

#endif //SPACEINVADERS_SPACEINVADERS_H