#include<SDL3_ttf/SDL_ttf.h>

#include<array>
#include<queue>
#include<string>

struct Line {
	std::string text;
	SDL_FRect rect;
};
class TextBox {
public:
	static const int NB_LINE_MAX = 5;
private:
	SDL_FRect rect;
	std::array<Line, NB_LINE_MAX> lines;
	int lastUsedLine;
	void pushLine(std::string s);
public:
	TextBox() = default;
	TextBox(SDL_FRect rect);
	void render(SDL_Renderer* renderer);
	void pushNewText(std::string newText);
};