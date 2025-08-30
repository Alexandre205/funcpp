#pragma once
#include<SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<string>
#include"Donjon.h"
namespace AppUtilities {
	void renderText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_FRect rect, SDL_Color backgroundColor);
	void renderDonjon(SDL_Renderer* renderer,Donjon* donjon, SDL_FRect renderArea);
}