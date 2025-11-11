#include "Enemy.h"

#include <SDL2/SDL_image.h>

int LoadEnemyTextures(EnemyTextures **enemies)
{
    (*enemies)->large = IMG_Load("Textures/Large.png");
    (*enemies)->medium = IMG_Load("Textures/Medium.png");
    (*enemies)->small = IMG_Load("Textures/Small.png");
    return 0;
}