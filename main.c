#include <stdio.h>
#include <time.h>

#include "SpaceInvaders.h"

int main()
{
	printf("Goodbye, world!\n");

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_bool quit = SDL_FALSE;

	float posX = 0, posY = 0;

	unsigned long lastTime = SDL_GetPerformanceCounter();
	unsigned long currentTime = 0;

	while (!quit) {
		currentTime = SDL_GetPerformanceCounter();;
		double deltaTime = (double)((currentTime - lastTime) / (double)SDL_GetPerformanceFrequency());
		lastTime = currentTime;
		SDL_Event e;
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
			quit = SDL_TRUE;
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			quit = SDL_TRUE;
		}
		if (e.key.state == SDL_PRESSED)
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_LEFT: posX -= 100*deltaTime; break;
				case SDLK_RIGHT: posX += 100*deltaTime; break;
				case SDLK_UP: posY -= 100*deltaTime; break;
				case SDLK_DOWN: posY += 100*deltaTime; break;
			}
		}

		posX = (posX < 0)? 600: (int)posX%600;
		posY = (posY < 0)? 800: (int)posY%800;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		SDL_Rect test = {posX,posY, 20,20};
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		//SDL_RenderDrawRect(renderer, &test);
		SDL_RenderFillRect(renderer, &test);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
