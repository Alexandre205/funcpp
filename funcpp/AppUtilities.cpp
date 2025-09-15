#include"AppUtilities.h"
#include"AffichageConsole.h"
#include"Salle.h"

void AppUtilities::renderText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_FRect rect, SDL_Color backgroundColor) {
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), 0, {0,0,0,255}, 0);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderTexture(renderer, texture,NULL,&rect);
	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surface);
}
void AppUtilities::renderDonjon(SDL_Renderer* renderer,Donjon* donjon, SDL_FRect renderArea) {
	renderArea.x += 50;
	renderArea.y += 25;
	renderArea.w -= 100;
	renderArea.h -= 50;
	SDL_FRect room{ renderArea.x,renderArea.y,200,100 };
	
	
	//rooms
	SDL_SetRenderDrawColor(renderer, 122, 122, 0, 255);
	for (float i{ 0 }; i < 3; i++) {
		room.y = renderArea.y + (renderArea.h * (i / 2)) - ((room.h/2) * i);
		for (float j{ 0 }; j < 3; j++) {
			room.x = renderArea.x + (renderArea.w * (j / 2)) - ((room.w/2) * j);
			int roomY = donjon->getCurrentY() + ((int)i - 1);
			int roomX = donjon->getCurrentX() + ((int)j - 1);
			if (donjon->isValidRoom(roomY,roomX) && !donjon->getRoom(roomY,roomX)->isState(SalleType::Wall)) {
				SDL_RenderFillRect(renderer, &room);
			}
		}
		room.x = renderArea.x;
	}

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//corridor horizontaux
	SDL_FRect corridor1{ renderArea.x + room.w,renderArea.y + room.h / 3,325,33 };
	for (int i{ 0 }; i < 3; i++) {
		corridor1.y =  190 * i + renderArea.y + room.h/3; //d'ou il sort 190
		for (int j{ 0 }; j < 2; j++) {
			corridor1.x += (corridor1.w+room.w)*j;
			int roomY = donjon->getCurrentY() + ((int)i - 1);
			int roomX = donjon->getCurrentX() + ((int)j - 1);
			if (donjon->isValidRoom(roomY, roomX) && donjon->getRoom(roomY, roomX)->hasEastConnexion()) {
				SDL_RenderFillRect(renderer, &corridor1);
			}
		}
		corridor1.x = renderArea.x + room.w;
	}
	//corridor verticaux
	SDL_FRect corridor2{ renderArea.x + (room.w / 2 - (room.w/12)),renderArea.y + room.h,33,87.5};
	for (int i{ 0 }; i < 2; i++) {
		for (int j{ 0 }; j < 3; j++) {
			int roomY = donjon->getCurrentY() + ((int)i - 1);
			int roomX = donjon->getCurrentX() + ((int)j - 1);
			if (donjon->isValidRoom(roomY, roomX) && donjon->getRoom(roomY, roomX)->hasSouthConnexion()) {
				SDL_RenderFillRect(renderer, &corridor2);
			}
			corridor2.x += 525; //+-525
		}
		corridor2.x = renderArea.x + (room.w / 2 - (room.w / 12));
		corridor2.y = room.h+corridor2.y+corridor2.h;
	}
}