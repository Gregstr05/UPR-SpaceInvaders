#include <stdio.h>
#include <time.h>

#include "SpaceInvaders.h"

int main()
{
	printf("Goodbye, world!\n");

	GameState gameState;
	Init(&gameState);

	GameTextures textures;
	LoadEnemyTextures(&textures.enemies);

	float posX = 0, posY = 0;

	unsigned long lastTime = SDL_GetPerformanceCounter();
	unsigned long currentTime = 0;

	while (!gameState.bShouldClose) {
		currentTime = SDL_GetPerformanceCounter();;
		double deltaTime = (double)((currentTime - lastTime) / (double)SDL_GetPerformanceFrequency());
		lastTime = currentTime;

		SDL_Event e;
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
			gameState.bShouldClose = SDL_TRUE;
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			gameState.bShouldClose = SDL_TRUE;
		}

		Update(deltaTime, &gameState);

		SDL_SetRenderDrawColor(gameState.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(gameState.renderer);

		Render(&gameState, &textures);

		SDL_RenderPresent(gameState.renderer);

	}

	Destroy(&gameState);

	return 0;
}
