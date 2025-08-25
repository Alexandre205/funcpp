#include"Game.h"
#include"GameState.h"
#include"Ressources.h"
#include"Utilitaire.h"

Game::Game() : requestQuit{false} {
	Ressources::initRessources();
	//Utilitaire::initSeed();
	setCurrentState(new GameStateStartMenu(*this));
}
SDL_AppResult Game::update(){
	currentState->update();
	if (requestQuit) {
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}
void Game::render(SDL_Renderer* renderer){
	currentState->render(renderer);
}
void Game::processInput(SDL_Event* event){
	currentState->processInput(event);
}
void Game::setCurrentState(GameState* state) {
	//delete currentState; //remplacer par des pointeur intelligent pour pouvoir garder des pointeurs pour des previousState
	currentState = state;
}
void Game::requestClosing() {
	requestQuit = true;
}