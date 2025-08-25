#pragma once
#include<SDL3/SDL.h>
#include<array>
#include"Option.h"
#include"DungeonGenerator.h"
#include"Donjon.h"
#include"TextBox.h"
class Game;
class GameState
{
public:
    GameState(Game& RefGame);
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void update() = 0;
    virtual void processInput(SDL_Event* event) = 0;
    virtual ~GameState();
protected:
    Game& game;
};
class GameStateStartMenu : public GameState {
private:
    std::array<Option, 3> options;
    int cursor;
public:
    GameStateStartMenu(Game& refGame);
    void render(SDL_Renderer* renderer);
    void update(); 
    void processInput(SDL_Event* event);
};
class GameStateDonjon : public GameState {
private:
    TextBox textBox;
public:
    GameStateDonjon(Game& refGame);
    void render(SDL_Renderer* renderer);
    void update();
    void processInput(SDL_Event* event);
};
class GameStateFight : public GameState {
private:

public:
    GameStateFight(Game& refGame);
    void render(SDL_Renderer* renderer);
    void update();
    void processInput(SDL_Event* event);
};
class GameStateMenuOverlay : public GameState {
private:
    GameState* lastState;
public:
    GameStateMenuOverlay(Game& refGame,GameState* lastState);
    void render(SDL_Renderer* renderer);
    void update();
    void processInput(SDL_Event* event);
};