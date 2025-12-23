
#include "UserInterface.h"


void RenderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y)
{
    if (!font) return;
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void RenderUI(SDL_Renderer *renderer, GameData *data, GameTextures *textures)
{
    SDL_Color white = {255, 255, 255, 255};

    char scoreStr[32];
    sprintf(scoreStr, "SCORE: %05d", data->score);
    RenderText(renderer, textures->font, scoreStr, white, 20, 20);

    RenderText(renderer, textures->font, "LIVES: ", white, 20, SCREEN_HEIGHT - 40);

    SDL_Rect src = {0, 0, 13, 12};
    for (int i = 0; i < data->player.lives; i++)
    {
        SDL_Rect dst = {170 + (i * 35), SCREEN_HEIGHT - 45, 26, 24};
        SDL_RenderCopy(renderer, textures->player.player, &src, &dst);
    }
}
