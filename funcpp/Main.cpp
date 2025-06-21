#include"Perso.h"
#include"Fight.h"
#include"Monstre.h"
#include"Effets.h"
#include"Consommable.h"
#include"Competence.h"
#include"Utilitaire.h"
#include"AffichageConsole.h"
#include"InputConsole.h"
#include"FileManagement.h"
#include"Salle.h"
#include"Donjon.h"

int main(int argc, char* argv[]) {
	//Utilitaire::nettoyerLog();
	Perso p1{ "Alex",100,10,50,50,50 };
	p1.apprendreCompetence(new Competence{ "attaque", "al", Effets::infligerDegat, "15", new MonoCible(), 0 });
	p1.apprendreCompetence(new Competence{ "super attaque","al",Effets::infligerDegat,"100",new MultiCible(),10 });

	Donjon d{&p1,3,5,1,1};
	Affichage::displayDonjon(d);
	while (true) {
		d.move();
		std::cout << "\033[2J\033[1;1H"; //clear console
		Affichage::displayDonjon(d);
	}
	Affichage::afficher("\n\nFIN");
	return EXIT_SUCCESS;
}