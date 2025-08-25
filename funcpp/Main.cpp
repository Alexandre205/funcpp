#define SDL_MAIN_USE_CALLBACKS 1 
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include<SDL3_ttf/SDL_ttf.h>

#include"Utilitaire.h"
#include"Ressources.h"
#include"Game.h"

static SDL_Window* window;
static SDL_Renderer* renderer;
static Game* game;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetAppMetadata("funcpp", "1.0", "a game in c++");
    if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init() || !SDL_CreateWindowAndRenderer("exemple", 1600, 900, 0, &window, &renderer)) {
        SDL_Log(SDL_GetError());
        return SDL_APP_FAILURE;
    }
    game = new Game();
    
	return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    game->processInput(event);
	return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppIterate(void* appstate) {
    SDL_AppResult result = game->update();
    game->render(renderer);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
	return result;
}
#include"DungeonGenerator.h"
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	TTF_Quit();
	SDL_Quit();
    delete game;
    Affichage::afficher("\n\nFIN");
}
//int main(int argc, char* argv[]) {
//	Ressources::initRessources();
//	Utilitaire::initSeed();
//	Perso p1 = Obtention::getNewStartPerso();
//	//Perso p1 = { "Alex",{100,10,50,50,50,50,50} }; p1.apprendreCompetence(new Competence{ "attaque","al",Effets::infligerDegat,"15",Ciblage::Mono,0 });p1.apprendreCompetence(new Competence{ "super attaque","al",Effets::infligerDegat,"100",Ciblage::Multi,10 });p1.apprendreCompetence(new Competence{ "skip","al",Effets::infligerDegat,"0",Ciblage::Self,0,-1});p1.apprendreCompetence(new Competence{ "Suicide","al",Effets::infligerDegat,"u.pv",Ciblage::Self,0,100});p1.addConsumable(new Consommable{ "verte","soin",0,Effets::soinPvEtPm,"10",Ciblage::Self,100 });
//	DungeonGenerator::generateDonjon(&p1)->explore();
//
//
//	Affichage::afficher("\n\nFIN\n");
//	
//	return EXIT_SUCCESS;
//}