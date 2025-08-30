#include "GameState.h"
#include "Game.h"
#include"AppUtilities.h"
#include"Ressources.h"
#include<SDL3_ttf/SDL_ttf.h>


GameState::GameState(Game& game) : game{game}{
}
GameState::~GameState() {
}

GameStateStartMenu::GameStateStartMenu(Game& game) : GameState{ game }, cursor{0} {
	options[0] = { {500,600,100,50},"New Game",[&game,this]() {game.setCurrentState(new GameStateCreatingCharacter(game)); } };
	options[1] = { {700,600,100,50},"Continue",[&game]() {game.setCurrentState(new GameStateDonjon(game)); }};
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
	this->textBox = {{25,625,1550,250} };
	game.setDonjon();
	game.startExploring();
}
void GameStateDonjon::update() {

}
void GameStateDonjon::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_FRect rect = { 125,50,1350,525 };//espace d'affichage du donjon
	SDL_RenderFillRect(renderer,&rect);
	textBox.render(renderer);
	AppUtilities::renderDonjon(renderer, game.getDonjon(), rect);
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
	this->textBox = {{25,625,1550,250} };
}
void GameStateFight::update() {

}
void GameStateFight::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_TRANSPARENT);
	SDL_FRect rects[3];
	rects[0] = { 725,200,150,250 };
	rects[1] = { 425,200,150,250 };
	rects[2] = { 1025,200,150,250 };
	SDL_RenderFillRects(renderer, rects,3);
	textBox.render(renderer);
}
void GameStateFight::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		TextBox* textBox;
		switch (event->key.key) {
		case SDLK_SPACE:
			textBox = new TextBox{{25,625,1550,250} };
			game.setCurrentState(new GameStateMenuOverlay(game, this, { 225,50,1050,550 }, { 255,255,255,100 }, { {{525,250,100,50},"lol",[textBox]() {textBox->pushNewText("lol"); }},{{725,250,100,50},"lul",[textBox]() {textBox->pushNewText("lul"); }} }, { "text","oui" }, textBox));
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

GameStateCreatingCharacter::GameStateCreatingCharacter(Game& game) : GameState(game), cursor{ (int)arrStat.size() }, cursorValMax{cursor}, showSpellSelection{ false } {
	//Démarrer l'input de text ici avec SDL_StartTextInput(window); quand window sera plus global
	std::array<std::string, Entite::NB_STAT> text = {"Life point","Mana point","Physical power","Magical power","Physical defence","Magical defence","Agility    "};
	nameBox = { 500,50,200,75 };
	for (int i{ 0 }; i < arrStat.size();i++) {
		arrStat[i].value = 15;
		arrStat[i].text = text[i];
		arrStat[i].positionValue = { 500, (float)(100 * (i + 1.5)) ,100,75};
	}
	for (int i{ 0 }; i < arrComp.size(); i++) {
		arrComp[i] = Ressources::dataPlayerComp[1][i];
	}
}
void GameStateCreatingCharacter::update() {

}
void GameStateCreatingCharacter::render(SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 96);
	SDL_Color color{ 0,255,0,255 };

	//affiche la box autour des boxe
	SDL_FRect choice;
	if (!showSpellSelection) {
		if (cursor < arrStat.size()) {
			choice = { arrStat[cursor].positionValue.x - arrStat[cursor].positionValue.w / 2.5f,arrStat[cursor].positionValue.y - arrStat[cursor].positionValue.h / 2.5f,
				arrStat[cursor].positionValue.w * 1.75f,arrStat[cursor].positionValue.h * 1.75f };
		}
		else {
			choice = { nameBox.x - nameBox.w / 2.5f,nameBox.y - nameBox.h / 2.5f,nameBox.w * 1.75f,nameBox.h * 1.75f };
		}
	}
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &choice);

	//Afficher la partie stats
	SDL_FRect nameTag{nameBox.x-250,nameBox.y,200,nameBox.h};
	AppUtilities::renderText(renderer, font, "Name", nameTag, color);
	AppUtilities::renderText(renderer, font, name, nameBox, color);
	for (StatRepresentation ar : arrStat) {
		SDL_FRect textPos{ ar.positionValue.x-250,ar.positionValue.y,200,ar.positionValue.h};
		AppUtilities::renderText(renderer, font, ar.text, textPos, color);
		AppUtilities::renderText(renderer, font, std::to_string(ar.value), ar.positionValue,color);
	}
	if (showSpellSelection) {
		SDL_FRect pos{1100,150,300,100};
		SDL_FRect choicePos{pos.x-50,pos.y - 25+(cursor*150),pos.w + 100,pos.h + 50};
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &choicePos);
		for (int i{ 0 }; i < arrComp.size();i++) {
			AppUtilities::renderText(renderer, font, arrComp[i].getNom().c_str(), pos, color);
			pos.y = 150 + (float)(150*(i+1));
		}
	}
}
void GameStateCreatingCharacter::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_SPACE:break;
		case SDLK_ESCAPE:
			game.setCurrentState(new GameStateStartMenu(game));
			break;
		case SDLK_RETURN:
			if (!showSpellSelection) {
				showSpellSelection = true;
				cursorValMax = (int)arrComp.size() - 1;
				cursor = 0;
			}
			else {
				std::array<int, Entite::NB_STAT> stats;
				for (int i{ 0 }; i < stats.size(); i++) {
					stats[i] = arrStat[i].value;
				}
				game.setPlayer(name, stats, arrComp[cursor]);
				game.setCurrentState(new GameStateDonjon(game));
			}
			break;
		case SDLK_UP:
			cursor--;
			if (cursor < 0) {
				cursor = cursorValMax;
			}
			break;
		case SDLK_RIGHT:
			if (cursor < cursorValMax && !showSpellSelection) {
				arrStat[cursor].value++; //pas si plus de point a distribuer
			}
			break;
		case SDLK_DOWN:
			cursor++;
			if (cursor > cursorValMax) {
				cursor = 0;
			}
			break;
		case SDLK_LEFT:
			if (cursor < cursorValMax && arrStat[cursor].value > 15 && !showSpellSelection) {
				arrStat[cursor].value--; //besoin de certain filtre
			}
			break;
		case SDLK_BACKSPACE:
			if (cursor == arrStat.size() && !name.empty()) {
				name.pop_back();
			}
			break;
		}
	}

	if (event->type == SDL_EVENT_TEXT_INPUT && cursor == arrStat.size() && name.size() <= 16) {
		name.append(event->text.text);
	}
}

GameStateMenuOverlay::GameStateMenuOverlay(Game& refGame, GameState* lastState, SDL_FRect menuArea, SDL_Color backgroundColor, std::vector<Option> options, std::vector<std::string> texts, TextBox* textBox) :
	GameState{ refGame }, lastState{ lastState }, menuArea{ menuArea }, backgroundColor{ backgroundColor }, cursor {0}, 
	options{ options }, texts{ texts }, textBox{ textBox } {

}
GameStateMenuOverlay::GameStateMenuOverlay(Game& refGame, GameState* lastState, SDL_FRect menuArea,SDL_Color backgroundColor) : 
	GameStateMenuOverlay{ refGame,lastState,menuArea,backgroundColor,{},{},nullptr } {

}
void GameStateMenuOverlay::update() {
	
}
void GameStateMenuOverlay::render(SDL_Renderer* renderer) {
	lastState->render(renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_RenderFillRect(renderer, &menuArea);
	if (!options.empty()) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200);
		SDL_FRect rect{ options[cursor].getRect().x - options[cursor].getRect().w / (float)2.5,options[cursor].getRect().y - options[cursor].getRect().h / (float)2.5,
		options[cursor].getRect().w * (float)1.75,options[cursor].getRect().h * (float)1.75 };
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
		for (Option option : options) {
			option.render(renderer);
		}
	}
	if (textBox) {
		textBox->render(renderer);
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}
void GameStateMenuOverlay::processInput(SDL_Event* event) {
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_SPACE:
			if (!options.empty()) {
				options[cursor].trigger();
			}
			break;
		case SDLK_ESCAPE:
			game.setCurrentState(lastState);
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