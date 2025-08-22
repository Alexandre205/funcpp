#pragma once
#include<SDL3/SDL.h>
#include<functional>
#include<string>
class Option {
private:
	SDL_FRect rect;
	std::string text;
public:
	Option() = default;
	Option(SDL_FRect rect, std::string text);
	void render(SDL_Renderer* renderer);
	SDL_FRect getRect();
};