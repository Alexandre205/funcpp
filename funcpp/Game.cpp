#include"Game.h"
#include"GameState.h"
#include"Ressources.h"
#include"AppUtilities.h"
#include"Utilitaire.h"

Game::Game() : requestQuit{ false }, donjon{ nullptr }, player{nullptr} {
	Ressources::initRessources();
	Utilitaire::initSeed();
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
void Game::setPlayer(std::string nom,std::array<int,Entite::NB_STAT> stats,Competence choseComp) {
	player = new Perso{nom,stats};
	player->apprendreCompetence(new Competence(Ressources::dataPlayerComp[0][0]));//competence de base
	player->apprendreCompetence(new Competence(choseComp));
}
void Game::setDonjon() {
	if (player) {
		donjon = DungeonGenerator::generateDonjon(player);
	}
}
Donjon* Game::getDonjon() {
	return donjon;
}
void Game::startExploring() {
	if (donjon) {
		
		//donjon->explore();
	}
}