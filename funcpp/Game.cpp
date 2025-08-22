#include"Game.h"
#include"GameState.h"
#include"Ressources.h"
#include"Utilitaire.h"

Game::Game() {
	Ressources::initRessources();
	Utilitaire::initSeed();
	setCurrentState(new GameStateStartMenu(*this));
}
void Game::update(){}
void Game::render(SDL_Renderer* renderer){
	currentState->render(renderer);
	
}
SDL_AppResult Game::processInput(SDL_Event* event){
	return currentState->processInput(event);
}
void Game::setCurrentState(GameState* state) {
	//delete currentState; //remplacer par des pointeur intelligent pour pouvoir garder des pointeurs pour des previousState
	currentState = state;
}