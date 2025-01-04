#include"erreurHandler.h"

void nettoyerLog() {
	std::ofstream fichier{ NOM_FICHIER, std::ofstream::out | std::ofstream::trunc };
	fichier.close();
}
std::string dateAujourdhui() {
	std::time_t current_time = std::time(nullptr);
	std::tm local_time;
	localtime_s(&local_time, &current_time);
	char output[50];
	strftime(output, 50, "%d/%m/%y, %H:%M:%S", &local_time);
	return output;
}
void testHandler(bool test,const char* message,bool afficheSucces) {
	std::ofstream fichier;
	fichier.open(NOM_FICHIER, std::ios::app);
	if (fichier) {
		if (test) {
			if (afficheSucces) {
				fichier << dateAujourdhui() + ", " + message + " : SUCCES\n";
			}
		}
		else {
			fichier << dateAujourdhui() + ", " + message + " : FAILURE\n";
			exit(EXIT_FAILURE);
		}
		fichier.close();
	}
	else {
		std::cout << "Fichier log non ouvert";
	}
}
void writeInLog(const char* message) {
	std::ofstream fichier{ NOM_FICHIER,std::ios::app };
	fichier << dateAujourdhui() + " , " + message + "\n";

}