#include <stdlib.h>

#include "SpaceInvaders.h"

#include <time.h>

#include "Helpers.h"

void Init(GameState *state)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
        exit(1);
    }

    state->window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (state->window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (state->renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    srand((unsigned int)time(NULL));

    state->bShouldClose = SDL_FALSE;
}

void InitGameData(GameData *data)
{
    int totalGridWidth = (11 * 24) + ((11 - 1) * 8);
    int startX = ((SCREEN_WIDTH - totalGridWidth) / 2) - 44;

    int currentEnemyIndex = 0;
    for (int row = 0; row < NUM_ENEMIES/11; row++)
    {
        EnemyType type;
        if (row == 0) {
            type = Small;
        } else if (row == 1 || row == 2) {
            type = Medium;
        } else { // rows 3 and 4
            type = Large;
        }

        for (int col = 0; col < 11; col++)
        {
            int posX = startX + (col * (24 + 20));
            int posY = 80 + (row * (24 + 8));

            InitEnemy(&data->enemies[currentEnemyIndex], type, posX, posY);
            currentEnemyIndex++;
        }
    }

    data->bPlayerProjectileActive = SDL_FALSE;

    data->alienDirection = 1;
    data->alienMoveTimer = 0.0f;
    data->alienMoveInterval = 0.5f;
    data->numActiveEnemyProjectiles = 0;

    data->alienFireTimer = 0.0f;
    data->alienFireInterval = 1.5f;

    InitPlayer(&data->player);
}

void LoadTextures(SDL_Renderer *renderer, GameTextures *textures)
{
    LoadEnemyTextures(renderer, &textures->enemies);
    LoadPlayerTextures(renderer, &textures->player);
    LoadProjectileTextures(renderer, &textures->projectiles);
}

void DestroyTextures(GameTextures *textures)
{
    DestroyEnemyTextures(&textures->enemies);
    DestroyPlayerTextures(&textures->player);
    DestroyProjectileTextures(&textures->projectiles);
}

void Destroy(GameState *state)
{
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    IMG_Quit();
    SDL_Quit();
}

void Update(double deltaTime, GameState *state, GameData *gameData)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: state->bShouldClose = SDL_TRUE; break;
            case SDL_KEYDOWN: switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE: state->bShouldClose = SDL_TRUE; break;
                case SDLK_SPACE: if (gameData->bPlayerProjectileActive == SDL_FALSE){
                    gameData->bPlayerProjectileActive = SDL_TRUE;
                    InitProjectile(&gameData->playerProjectile, (SDL_Point){gameData->player.position.x+12, gameData->player.position.y+10}, PlayerProjectile);
                }; break;
                default: break;
            }
            default: break;
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    float moveSpeed = 200.0f; // pixels per second

    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
    {
        int newX = gameData->player.position.x - (int)(moveSpeed * deltaTime);
        if (newX < 0) newX = 0;
        gameData->player.position.x = newX;
    }

    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
    {
        int newX = gameData->player.position.x + (int)(moveSpeed * deltaTime);
        // Clamp to screen bounds (player width is 52 pixels)
        if (newX > SCREEN_WIDTH - 52) newX = SCREEN_WIDTH - 52;
        gameData->player.position.x = newX;
    }

    gameData->alienMoveTimer += (float)deltaTime;
    if (gameData->alienMoveTimer >= gameData->alienMoveInterval) {
        gameData->alienMoveTimer = 0;
        SDL_bool shouldFlip = SDL_FALSE;

        // Check if ANY alien will hit the edge in the CURRENT direction
        for (int i = 0; i < NUM_ENEMIES-1; i++) {
            if (!gameData->enemies[i].bAlive) continue;

            int nextX = gameData->enemies[i].position.x + (gameData->alienDirection * 15);
            if (gameData->alienDirection == 1 && nextX >= SCREEN_WIDTH - 24) {
                shouldFlip = SDL_TRUE;
                break;
            }
            if (gameData->alienDirection == -1 && nextX <= 0) {
                shouldFlip = SDL_TRUE;
                break;
            }
        }

        if (shouldFlip) {
            gameData->alienDirection *= -1; // Reverse
            for (int i = 0; i < NUM_ENEMIES-1; i++) {
                gameData->enemies[i].position.y += 16; // Move down
            }
        } else {
            for (int i = 0; i < NUM_ENEMIES-1; i++) {
                gameData->enemies[i].position.x += (gameData->alienDirection * 15);
            }
        }
    }

    gameData->alienFireTimer += (float)deltaTime;
    if (gameData->alienFireTimer >= gameData->alienFireInterval)
    {
        gameData->alienFireTimer = 0;
        int aliveCount = 0;
        int indices[NUM_ENEMIES];
        for(int i=0; i<NUM_ENEMIES; i++) if(gameData->enemies[i].bAlive) indices[aliveCount++] = i;

        if (aliveCount > 0 && gameData->numActiveEnemyProjectiles < MAX_PROJECTILES)
        {
            Enemy *enemy = &gameData->enemies[indices[rand() % aliveCount]];
            InitProjectile(&gameData->enemyProjectiles[gameData->numActiveEnemyProjectiles++], (SDL_Point){enemy->position.x + 8, enemy->position.y + 20}, EnemyProjectile);
        }
    }
    if (gameData->bPlayerProjectileActive)
    {
        UpdateProjectile(&gameData->playerProjectile, deltaTime);

        // Check Alien Collisions
        for (int i = 0; i < NUM_ENEMIES; i++)
        {
            Enemy *e = &gameData->enemies[i];
            if (e->bAlive && CHECK_COLLISION(gameData->playerProjectile.x, gameData->playerProjectile.y, 16, 24, e->position.x, e->position.y, 24, 24))
            {
                e->bAlive = SDL_FALSE;
                gameData->bPlayerProjectileActive = SDL_FALSE;
                gameData->alienMoveInterval -= 0.005f;
                break;
            }
        }

        // Out of Bounds check
        if (gameData->playerProjectile.y < 0) gameData->bPlayerProjectileActive = SDL_FALSE;
    }

    // --- 3. Update Enemy Projectile Pool ---
    for (int i = 0; i < gameData->numActiveEnemyProjectiles; i++)
    {
        Projectile *p = &gameData->enemyProjectiles[i];
        UpdateProjectile(p, deltaTime);

        SDL_bool hit = SDL_FALSE;
        // Check Player Collision
        if (CHECK_COLLISION(p->x, p->y, 16, 24, gameData->player.position.x, gameData->player.position.y, 26, 24))
        {
            gameData->player.lives--;
            hit = SDL_TRUE;
        }

        if (hit || p->y > SCREEN_HEIGHT + 30)
        {
            gameData->enemyProjectiles[i] = gameData->enemyProjectiles[gameData->numActiveEnemyProjectiles - 1];
            gameData->numActiveEnemyProjectiles--;
            i--;
        }
    }
}

void Render(GameState *state, GameTextures *textures, GameData *gameData)
{
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        RenderEnemy(&gameData->enemies[i], &textures->enemies, state->renderer);
    }

    for (int i = 0; i < gameData->numActiveEnemyProjectiles; i++)
    {
        RenderProjectile(&gameData->enemyProjectiles[i], &textures->projectiles, state->renderer);
    }

    if (gameData->bPlayerProjectileActive)
        RenderProjectile(&gameData->playerProjectile, &textures->projectiles, state->renderer);

    RenderPlayer(&gameData->player, &textures->player, state->renderer);
}