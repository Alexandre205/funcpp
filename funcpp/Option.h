#pragma once
#include<SDL3/SDL.h>
#include<functional>
#include<string>
#include<variant>



class Option {
private:
	SDL_FRect rect;
	std::string text;
	
	std::function<void()> onSelect;
public:
	Option() = default;
	Option(SDL_FRect rect, std::string text, std::function<void()> onSelect);
	void render(SDL_Renderer* renderer);
	SDL_FRect getRect();
	void trigger();
};