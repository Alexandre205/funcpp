#include "GameState.h"
#include "Game.h"

GameState::GameState(Game& game) : game{game}{
}
GameState::~GameState() {
}

GameStateStartMenu::GameStateStartMenu(Game& game) : GameState{ game }, cursor{0} {
	options[0] = { {500,600,100,50},"New Game" };
	options[1] = { {700,600,100,50},"Continue" };
	options[2] = { {900,600,100,50},"Quit" };
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
SDL_AppResult GameStateStartMenu::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_SPACE: //confirm
			switch (cursor) {
			case 0:game.setCurrentState(new GameStateDonjon(game)); break;
			case 1:break;
			case 2:return SDL_APP_SUCCESS;
			}
			
			break;
		case SDLK_ESCAPE: //back
			return SDL_APP_SUCCESS;
			break;
		case SDLK_UP: break; //up
		case SDLK_RIGHT: //right
			cursor++;
			if (cursor >= options.size()) {
				cursor = 0;
			}
			break;
		case SDLK_DOWN:break;   //down
		case SDLK_LEFT: //left
			cursor--;
			if (cursor < 0) {
				cursor = (int)options.size() - 1;
			}
			break;
		}
	}
	return SDL_APP_CONTINUE;
}
GameStateDonjon::GameStateDonjon(Game& game) : GameState{game} {

}
void GameStateDonjon::update() {

}
void GameStateDonjon::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_FRect rect = { 25,25,500,250 };
	SDL_RenderFillRect(renderer,&rect);
}
SDL_AppResult GameStateDonjon::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_SPACE:
			game.setCurrentState(new GameStateFight(game));
			break; //confirm
		case SDLK_ESCAPE:
			game.setCurrentState(new GameStateStartMenu(game));
			break; //back
		case SDLK_UP: break;    //up
		case SDLK_RIGHT:break;  //right
		case SDLK_DOWN:break;   //down
		case SDLK_LEFT:break;   //left
		}
	}
	return SDL_APP_CONTINUE;
}
GameStateFight::GameStateFight(Game& game) : GameState{game} {

}
void GameStateFight::update() {

}
void GameStateFight::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_FRect rect{ 750,400,100,50 };
	SDL_RenderFillRect(renderer, &rect);
}
SDL_AppResult GameStateFight::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_SPACE:
			game.setCurrentState(new GameStateMenuOverlay(game,this));
			break; //confirm
		case SDLK_ESCAPE:
			game.setCurrentState(new GameStateDonjon(game));
			break; //back
		case SDLK_UP: break;    //up
		case SDLK_RIGHT:break;  //right
		case SDLK_DOWN:break;   //down
		case SDLK_LEFT:break;   //left
		}
	}
	return SDL_APP_CONTINUE;
}
GameStateMenuOverlay::GameStateMenuOverlay(Game& game, GameState *lastState) : GameState{ game }, lastState{lastState} {

}
void GameStateMenuOverlay::update() {
	
}
void GameStateMenuOverlay::render(SDL_Renderer* renderer) {
	lastState->render(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_FRect rect{ 1000,450,550,350 };
	SDL_RenderFillRect(renderer, &rect);
}
SDL_AppResult GameStateMenuOverlay::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_SPACE:break; //confirm
		case SDLK_ESCAPE:
			game.setCurrentState(lastState);
			break; //back
		case SDLK_UP: break;    //up
		case SDLK_RIGHT:break;  //right
		case SDLK_DOWN:break;   //down
		case SDLK_LEFT:break;   //left
		}
	}
	return SDL_APP_CONTINUE;
}