#include <stdio.h>
#include <time.h>

#include "SpaceInvaders.h"

int main()
{
	GameState gameState;
	Init(&gameState);

	GameTextures textures;
	LoadTextures(gameState.renderer, &textures);

	GameData gameData;
	InitGameData(&gameData);

	unsigned long lastTime = SDL_GetPerformanceCounter();
	unsigned long currentTime = 0;

	while (!gameState.bShouldClose) {
		currentTime = SDL_GetPerformanceCounter();;
		double deltaTime = (double)(currentTime - lastTime) / (double)SDL_GetPerformanceFrequency();
		lastTime = currentTime;

		Update(deltaTime, &gameState, &gameData);

		SDL_SetRenderDrawColor(gameState.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(gameState.renderer);

		Render(&gameState, &textures, &gameData);

		SDL_RenderPresent(gameState.renderer);
	}

	DestroyTextures(&textures);
	Destroy(&gameState);

	return 0;
}
