#include"TextBox.h"

TextBox::TextBox(SDL_Color fontColor, SDL_Color backgroundColor, SDL_FRect rect) :fontColor{ fontColor }, backgroundColor{ backgroundColor }, rect{ rect }, lastUsedLine{0} {
	float heigth{ rect.h / lines.size() };
	float yPos{rect.y};
	for (int i{ 0 }; i < lines.size(); i++) {
		lines[i].rect = {rect.x,yPos,rect.w,heigth} ;
		lines[i].text = "";
		yPos += heigth;
	}
}
void TextBox::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_RenderFillRect(renderer, &rect);
	TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 96);
	for (Line line : lines) {
		//50 char + '\0'
		std::string s( 51,' ' );
		s.replace(s.begin(),s.begin()+(int)line.text.size()+1, line.text);
		SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, s.c_str(), 0, fontColor, 0);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderTexture(renderer, texture, NULL, &line.rect);
		SDL_DestroyTexture(texture);
		SDL_DestroySurface(surface);
	}
}
void TextBox::pushNewText(std::string newText) {
	//si plus grand que 50 char alors séparer en plusieurs lignes
	if (!newText.empty()) {
		if (newText.size() < 50) {
			pushLine(newText);
		}
		else {
			std::string fiftyFirstChar = newText.substr(0, 50);
			size_t lastSpace = fiftyFirstChar.find_last_of(' ');
			if (lastSpace == std::string::npos) {
				pushLine(fiftyFirstChar);
				pushLine(newText.substr(50, newText.size()-1));
			}
			else {
				pushLine(fiftyFirstChar.substr(0, lastSpace));
				pushNewText(newText.substr(lastSpace, newText.size()));
			}
		}
	}
}
void TextBox::pushLine(std::string s) {
	if (lastUsedLine < lines.size()) {
		lines[lastUsedLine].text = s;
		lastUsedLine++;
	}
	else {
		for (int i{ 1 }; i < lines.size(); i++) {
			lines[i - 1].text = lines[i].text;
		}
		lines[lastUsedLine-1].text = s;
	}
}