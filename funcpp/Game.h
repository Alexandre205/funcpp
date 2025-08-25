#pragma once
#include<SDL3/SDL.h>
#include"Donjon.h"
#include"Perso.h"
class GameState;
class Game {
private:
    GameState* currentState;
    bool requestQuit;
    Perso* player;
    Donjon* donjon;
public:
    Game();
    void processInput(SDL_Event* event);
    SDL_AppResult update();
    void render(SDL_Renderer* renderer);
    void setCurrentState(GameState* newState);
    void requestClosing();
};