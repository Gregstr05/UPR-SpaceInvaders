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

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        exit(1);
    }

    srand((unsigned int)time(NULL));

    state->bShouldClose = SDL_FALSE;
}

void SpawnEnemies(GameData *gameData)
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
        } else {
            type = Large;
        }

        for (int col = 0; col < 11; col++)
        {
            int posX = startX + (col * (24 + 20));
            int posY = 80 + (row * (24 + 8));

            InitEnemy(&gameData->enemies[currentEnemyIndex], type, posX, posY);
            currentEnemyIndex++;
        }
    }
}

void InitGameData(GameData *data)
{
    data->phase = PHASE_MENU;
    LoadHighScores(data);

    SpawnEnemies(data);

    // Mothership starts dead
    data->enemies[NUM_ENEMIES - 1].type = MotherShip;
    data->enemies[NUM_ENEMIES - 1].bAlive = SDL_FALSE;

    data->motherShipSpawnTimer = 0.0f;
    data->motherShipSpawnInterval = 15.0f + (float)(rand() % 15);
    data->motherShipDirection = 1;

    data->bPlayerProjectileActive = SDL_FALSE;

    data->alienDirection = 1;
    data->alienMoveTimer = 0.0f;
    data->alienMoveInterval = 0.8f;
    data->numActiveEnemyProjectiles = 0;

    data->alienFireTimer = 0.0f;
    data->alienFireInterval = 1.5f;

    InitPlayer(&data->player);
    data->score = 0;
    data->shots = 0;
    data->nameCharIndex = 0;
    memset(data->playerName, '_', 6);
    data->playerName[6] = '\0';
}

void LoadTextures(SDL_Renderer *renderer, GameTextures *textures)
{
    LoadEnemyTextures(renderer, &textures->enemies);
    LoadPlayerTextures(renderer, &textures->player);
    LoadProjectileTextures(renderer, &textures->projectiles);
    textures->font = TTF_OpenFont("Fonts/PressStart2P-Regular.ttf", 24);
}

void DestroyTextures(GameTextures *textures)
{
    DestroyEnemyTextures(&textures->enemies);
    DestroyPlayerTextures(&textures->player);
    DestroyProjectileTextures(&textures->projectiles);
    TTF_CloseFont(textures->font);
}

void SaveScore(const char *name, int score)
{
    FILE *file = fopen("highscores.txt", "a");
    if (file == NULL) return;

    fprintf(file, "%s %d\n", name, score);
    fclose(file);
    printf("Score saved: %s - %d\n", name, score);
}

void LoadHighScores(GameData *data)
{
    data->numHighScores = 0;
    for (int i = 0; i < 5; i++) {
        strcpy(data->highScores[i].name, "---");
        data->highScores[i].score = 0;
    }

    FILE *file = fopen("highscores.txt", "r");
    if (file == NULL) return;

    HighScore current;
    while (fscanf(file, "%6s %d", current.name, &current.score) == 2)
    {
        for (int i = 0; i < 5; i++)
        {
            if (current.score > data->highScores[i].score)
            {
                // Shift down previous high scores
                for (int j = 4; j > i; j--)
                {
                    data->highScores[j] = data->highScores[j - 1];
                }

                data->highScores[i] = current;

                if (data->numHighScores < 5)
                    data->numHighScores++;

                break;
            }
        }
    }

    fclose(file);
}

void Destroy(GameState *state)
{
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    TTF_Quit();
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
            case SDL_KEYDOWN: SDL_Keycode key = event.key.keysym.sym; switch (key)
            {
                case SDLK_ESCAPE: state->bShouldClose = SDL_TRUE; break;
                case SDLK_SPACE: if (gameData->bPlayerProjectileActive == SDL_FALSE && gameData->phase == PHASE_PLAYING){
                    gameData->bPlayerProjectileActive = SDL_TRUE;
                    InitProjectile(&gameData->playerProjectile, (SDL_Point){gameData->player.position.x+12, gameData->player.position.y+10}, PlayerProjectile);
                    gameData->shots++;
                }; break;
                default:
                    {
                        if (key >= SDLK_a && key <= SDLK_z && gameData->nameCharIndex < 6) {
                            gameData->playerName[gameData->nameCharIndex] = (char)('A' + (key - SDLK_a));
                            gameData->nameCharIndex++;
                        }

                        else if (key == SDLK_BACKSPACE && gameData->nameCharIndex > 0) {
                            gameData->nameCharIndex--;
                            gameData->playerName[gameData->nameCharIndex] = '_';
                        }

                        else if (key == SDLK_RETURN && gameData->nameCharIndex > 0) {
                            for(int i = 0; i < 6; i++) if(gameData->playerName[i] == '_') gameData->playerName[i] = ' ';

                            SaveScore(gameData->playerName, gameData->score);
                            InitGameData(gameData);
                        }
                    } break;
            }
            default: break;
        }
    }

    switch (gameData->phase)
    {
        case PHASE_MENU: UpdateMenu(deltaTime, state, gameData); break;
        case PHASE_PLAYING: UpdateGamePlay(deltaTime, gameData); break;
        case PHASE_GAME_OVER: UpdateGameOver(deltaTime, state, gameData); break;
    }
}

void UpdateGamePlay(double deltaTime, GameData *gameData)
{
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    float moveSpeed = 200.0f; // Player movement speed, should move it to better place

    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
    {
        int newX = gameData->player.position.x - (int)(moveSpeed * deltaTime);
        if (newX < 0) newX = 0;
        gameData->player.position.x = newX;
    }

    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
    {
        int newX = gameData->player.position.x + (int)(moveSpeed * deltaTime);
        if (newX > SCREEN_WIDTH - 26) newX = SCREEN_WIDTH - 26;
        gameData->player.position.x = newX;
    }

    gameData->alienMoveTimer += (float)deltaTime;
    if (gameData->alienMoveTimer >= gameData->alienMoveInterval) {
        gameData->alienMoveTimer = 0;
        SDL_bool bShouldFlip = SDL_FALSE;
        gameData->bAlive = SDL_FALSE;

        // Check if ANY alien will hit the edge in the CURRENT direction
        for (int i = 0; i < NUM_ENEMIES-1; i++) {
            if (!gameData->enemies[i].bAlive) continue;

            gameData->bAlive = SDL_TRUE;

            if (gameData->enemies[i].position.y >= 520)
            {
                gameData->phase = PHASE_GAME_OVER;
                break;
            }
            int nextX = gameData->enemies[i].position.x + (gameData->alienDirection * 15);
            if (gameData->alienDirection == 1 && nextX >= SCREEN_WIDTH - 24) {
                bShouldFlip = SDL_TRUE;
                break;
            }
            if (gameData->alienDirection == -1 && nextX <= 0) {
                bShouldFlip = SDL_TRUE;
                break;
            }
        }

        if (bShouldFlip) {
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

    // All aliens are dead
    if (!gameData->bAlive)
    {
        gameData->bAlive = SDL_TRUE;
        SpawnEnemies(gameData);
        gameData->player.lives++;
    }

    if (!gameData->enemies[UFO_INDEX].bAlive)
    {
        gameData->motherShipSpawnTimer += (float)deltaTime;
        if (gameData->motherShipSpawnTimer >= gameData->motherShipSpawnInterval)
        {
            gameData->enemies[UFO_INDEX].bAlive = SDL_TRUE;
            gameData->motherShipDirection = (rand() % 2 == 0) ? 1 : -1;

            gameData->enemies[UFO_INDEX].position.y = 40;
            if (gameData->motherShipDirection == 1)
                gameData->enemies[UFO_INDEX].position.x = -32;
            else
                gameData->enemies[UFO_INDEX].position.x = SCREEN_WIDTH;

            gameData->motherShipSpawnTimer = 0.0f;
            gameData->motherShipSpawnInterval = 20.0f + (float)(rand() % 20);
        }
    }
    else
    {
        float ufoSpeed = 160.0f;
        gameData->enemies[UFO_INDEX].position.x += (int)(ufoSpeed * gameData->motherShipDirection * deltaTime);

        if (gameData->enemies[UFO_INDEX].position.x < -40 || gameData->enemies[UFO_INDEX].position.x > SCREEN_WIDTH + 40)
        {
            gameData->enemies[UFO_INDEX].bAlive = SDL_FALSE;
        }
    }

    gameData->alienFireTimer += (float)deltaTime;
    if (gameData->alienFireTimer >= gameData->alienFireInterval)
    {
        gameData->alienFireTimer = 0;
        int aliveCount = 0;
        int indices[NUM_ENEMIES-1];
        for(int i=0; i<NUM_ENEMIES-1; i++) if(gameData->enemies[i].bAlive) indices[aliveCount++] = i;

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
            int hitW = (e->type == MotherShip) ? 32 : 24;
            int hitH = (e->type == MotherShip) ? 14 : 24;
            if (e->bAlive && CHECK_COLLISION(gameData->playerProjectile.x, gameData->playerProjectile.y, /*It feels better to have a larger projectile hitbox for player projectiles*/ 8, 16, e->position.x, e->position.y, hitH, hitH))
            {
                e->bAlive = SDL_FALSE;
                gameData->bPlayerProjectileActive = SDL_FALSE;
                gameData->alienMoveInterval -= 0.005f;
                switch (e->type)
                {
                    case Small: gameData->score += 30; break;
                    case Medium: gameData->score += 20; break;
                    case Large: gameData->score += 10; break;
                    case MotherShip: gameData->score += GET_MOTHERSHIP_VALUE(gameData->shots); break;
                }
                break;
            }
        }

        // Out of Bounds check
        if (gameData->playerProjectile.y < 0) gameData->bPlayerProjectileActive = SDL_FALSE;
    }

    for (int i = 0; i < gameData->numActiveEnemyProjectiles; i++)
    {
        Projectile *p = &gameData->enemyProjectiles[i];
        UpdateProjectile(p, deltaTime);

        SDL_bool bHit = SDL_FALSE;
        // Check Player Collision
        if (CHECK_COLLISION(p->x, p->y, 16, 24, gameData->player.position.x, gameData->player.position.y, 26, 24))
        {
            gameData->player.lives--;
            bHit = SDL_TRUE;
        }

        if (bHit || p->y > SCREEN_HEIGHT + 30)
        {
            gameData->enemyProjectiles[i] = gameData->enemyProjectiles[gameData->numActiveEnemyProjectiles - 1];
            gameData->numActiveEnemyProjectiles--;
            i--;
        }
    }

    if (gameData->player.lives <= 0) {
        gameData->phase = PHASE_GAME_OVER;
    }
}

void UpdateGameOver(double deltaTime, GameState *state, GameData *gameData)
{

}

void UpdateMenu(double deltaTime, GameState *state, GameData *gameData)
{
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_SPACE])
    {
        gameData->phase = PHASE_PLAYING;
    }
}

void Render(GameState *state, GameTextures *textures, GameData *gameData)
{
    if (gameData->phase == PHASE_PLAYING)
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

    RenderUI(state->renderer, gameData, textures);
}
