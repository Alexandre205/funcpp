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
    TextBox textBox;
public:
    GameStateFight(Game& refGame);
    void render(SDL_Renderer* renderer);
    void update();
    void processInput(SDL_Event* event);
};
class GameStateCreatingCharacter : public GameState {
    struct StatRepresentation{
        int value;
        std::string text;
        SDL_FRect positionValue;
    };
private:
    int cursor;
    int cursorValMax;
    std::string name;
    SDL_FRect nameBox;
    std::array<StatRepresentation, Entite::NB_STAT> arrStat;
    bool showSpellSelection;
    std::array<Competence, 4> arrComp;
public:
    GameStateCreatingCharacter(Game& refGame);
    void render(SDL_Renderer* renderer);
    void update();
    void processInput(SDL_Event* event);
};
class GameStateMenuOverlay : public GameState {
private:
    GameState* lastState;
    SDL_FRect menuArea;
    SDL_Color backgroundColor;

    //those are facultative
    std::vector<Option> options;
    int cursor;
    std::vector<std::string> texts;
    TextBox* textBox;
public:
    GameStateMenuOverlay(Game& refGame, GameState* lastState, SDL_FRect menuArea, SDL_Color backgroundColor, std::vector<Option> options, std::vector<std::string> texts, TextBox* textBox);
    GameStateMenuOverlay(Game& refGame, GameState* lastState, SDL_FRect menuArea, SDL_Color backgroundColor);
    void render(SDL_Renderer* renderer);
    void update();
    void processInput(SDL_Event* event);
};