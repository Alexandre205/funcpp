#include"Option.h"
#include<SDL3_ttf/SDL_ttf.h>
Option::Option(SDL_FRect rect, std::string text) : rect{rect}, text{text} {
}
void Option::render(SDL_Renderer* renderer) {
	SDL_RenderFillRect(renderer, &rect);
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 96), text.c_str(), 0, {0,0,0,255}, 0);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_GetTextureSize(texture, NULL, NULL);
	SDL_RenderTexture(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surface);
}
SDL_FRect Option::getRect() {
	return rect;
}