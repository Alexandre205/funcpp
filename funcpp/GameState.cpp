#include "GameState.h"
#include "Game.h"
#include<SDL3_ttf/SDL_ttf.h>



GameState::GameState(Game& game) : game{game}{
}
GameState::~GameState() {
}

GameStateStartMenu::GameStateStartMenu(Game& game) : GameState{ game }, cursor{0} {
	options[0] = { {500,600,100,50},"New Game",[&game]() {game.setCurrentState(new GameStateDonjon(game)); } };
	options[1] = { {700,600,100,50},"Continue",[]() {} };
	options[2] = { {900,600,100,50},"Quit",[&game]() {game.requestClosing(); } };
}
void GameStateStartMenu::update() {

}
void GameStateStartMenu::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_FRect rect{ options[cursor].getRect().x - options[cursor].getRect().w /2,options[cursor].getRect().y - options[cursor].getRect().h/2,
		options[cursor].getRect().w*2,options[cursor].getRect().h*2};
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	for (Option option : options) {
		option.render(renderer);
	}
}
void GameStateStartMenu::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_SPACE:
			options[cursor].trigger();
			break;
		case SDLK_ESCAPE: 
				game.requestClosing();
			break;
		case SDLK_UP: break;
		case SDLK_RIGHT: 
			cursor++;
			if (cursor >= options.size()) {
				cursor = 0;
			}
			break;
		case SDLK_DOWN:break;
		case SDLK_LEFT:
			cursor--;
			if (cursor < 0) {
				cursor = (int)options.size() - 1;
			}
			break;
		}
	}
}

GameStateDonjon::GameStateDonjon(Game& game) : GameState{game} {
	this->textBox = { {0,0,0,255},{255,255,255,255},{25,625,1550,250} };
}
void GameStateDonjon::update() {

}
void GameStateDonjon::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_FRect rect = { 25,25,1550,575 }; //espace d'affichage du donjon
	SDL_RenderFillRect(renderer,&rect);
	textBox.render(renderer);
}
void GameStateDonjon::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_SPACE:
			game.setCurrentState(new GameStateFight(game));
			break; 
		case SDLK_ESCAPE:
			game.setCurrentState(new GameStateStartMenu(game));
			break;
		case SDLK_UP: 
			break;
		case SDLK_RIGHT:
			break; 
		case SDLK_DOWN:break;   
		case SDLK_LEFT:break;  
		}
	}

}

GameStateFight::GameStateFight(Game& game) : GameState{game} {

}
void GameStateFight::update() {

}
void GameStateFight::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_TRANSPARENT);
	SDL_FRect rects[4];
	rects[0] = { 25,625,1550,250 }; // espace d'affichage du texte // doit etre remplacer par TextBox
	rects[1] = { 725,200,150,250 };
	rects[2] = { 425,200,150,250 };
	rects[3] = { 1025,200,150,250 };
	SDL_RenderFillRects(renderer, rects,4);

}
void GameStateFight::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_SPACE:
			game.setCurrentState(new GameStateMenuOverlay(game,this));
			break; 
		case SDLK_ESCAPE:
			game.setCurrentState(new GameStateDonjon(game));
			break;
		case SDLK_UP: break;  
		case SDLK_RIGHT:break;
		case SDLK_DOWN:break;
		case SDLK_LEFT:break;
		}
	}
}

GameStateMenuOverlay::GameStateMenuOverlay(Game& game, GameState *lastState) : GameState{ game }, lastState{lastState} {

}
void GameStateMenuOverlay::update() {
	
}
void GameStateMenuOverlay::render(SDL_Renderer* renderer) {
	lastState->render(renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_TRANSPARENT);
	SDL_FRect rect{ 800,420,550,350 };
	SDL_RenderFillRect(renderer, &rect);
}
void GameStateMenuOverlay::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_SPACE:break;
		case SDLK_ESCAPE:
			game.setCurrentState(lastState);
			break; 
		case SDLK_UP: break;   
		case SDLK_RIGHT:break;  
		case SDLK_DOWN:break;   
		case SDLK_LEFT:break;   
		}
	}

}