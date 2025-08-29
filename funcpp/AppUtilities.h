#pragma once
#include<SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<string>
namespace AppUtilities {
	void renderText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_FRect rect, SDL_Color backgroundColor);
}