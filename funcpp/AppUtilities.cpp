#include"AppUtilities.h"

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
	SDL_SetRenderDrawColor(renderer, 122, 122, 0, 255);
	renderArea.x += 50;
	renderArea.y += 25;
	renderArea.w -= 100;
	renderArea.h -= 50;
	SDL_FRect room{ renderArea.x,renderArea.y,200,100 };
	for (float i{ 0 }; i < 3; i++) {
		room.y = renderArea.y + (renderArea.h * (i / 2)) - ((room.h/2) * i);
		for (float j{ 0 }; j < 3; j++) {
			room.x = renderArea.x + (renderArea.w * (j / 2)) - ((room.w/2) * j);
			//dessiner les connexions
			SDL_RenderFillRect(renderer, &room);
		}
		room.x = renderArea.x;
	}

}