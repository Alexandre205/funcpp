#pragma once
#include<SDL3/SDL.h>
class GameState;
class Game {
private:
    GameState* currentState;
public:
    Game();
    SDL_AppResult processInput(SDL_Event* event);
    void update();
    void render(SDL_Renderer* renderer);
    void setCurrentState(GameState* newState);
};