# UPR-SpaceInvaders
Simple space invaders clone using C and SDL2 for Introduction to programming course

> [!NOTE]
> Build with `cmake . -B build` and `cmake --build build`

## Update Loop
The update loop uses delta time (difference between the previous frame's timestamp and current frame's timestamp) which is used to offset the effects of different frame times.
Without delta time any movement would be dependent on the frame time itself, meaning with shorter frame times (higher frames per second) things would happen quicker, because the update loop would run many more times, than with longer frame times (lower frames per second).
```c++
currentTime = SDL_GetPerformanceCounter();
double deltaTime = (double)(currentTime - lastTime) / (double)SDL_GetPerformanceFrequency();
lastTime = currentTime;

Update(deltaTime, &gameState, &gameData);
```
The delta time gets calculated by comparing the previous and current values of the *high resolution counter* that is accessible from the operating system (done with `SDL_GetPerformanceCounter()`). This gives us the difference between the frames, but different operating systems might use different units for their high resolution counter, so we divide it by the units per second, which we get from `SDL_GetPerformanceFrequency()`, and now we know, that our delta time is now expressed as seconds, but it's a double precision floating point number, because it should preferably not take a second for one frame/update.

### Input
I use `SDL_KEYDOWN` event for single shot actions, like firing.
```c++
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
                gameData->shots++;
            }; break;
            default: break;
        }
        default: break;
    }
}
```
This loop is ran every frame, to pop all events from the event queue, if any of the events that happened the previous frame happens to be a `SDL_KEYDOWN` the appropriate switch case is executed.

For continuous input (player movement) I use SDL's KeyboardState array, to check if any specific key is pressed.
```c++
const Uint8 *keystate = SDL_GetKeyboardState(NULL);

// the keystate array is an array which can be indexed with button scancodes
// individual keys/indexes can have a value of either 1 => Pressed or 0 => not pressed
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
```
### Alien swarm movement
The alien swarm moves as one unit always to one end of the screen, then moving down and going to the other side.
I check if any alien could get out of bounds on the next update to determine if the edge of the screen has been reached, which is useful to react to the changing nature of the swarm due to the player's objective to destroy them.
```c++
gameData->alienMoveTimer += (float)deltaTime;
if (gameData->alienMoveTimer >= gameData->alienMoveInterval) {
    gameData->alienMoveTimer = 0;
    SDL_bool bShouldFlip = SDL_FALSE;

    // Check if ANY alien will hit the edge in the CURRENT direction
    for (int i = 0; i < NUM_ENEMIES-1; i++) {
        if (!gameData->enemies[i].bAlive) continue;

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
```
I loop through the enemy array purposely skipping the last element, because that one is reserved for the mother ship/UFO that moves independently of the swarm.

