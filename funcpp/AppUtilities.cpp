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