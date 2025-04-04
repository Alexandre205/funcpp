#include "Utilitaire.h"
#include<map>
#include<iostream>
#include<queue>
#include<stack>
#include<fstream>
#include<ctime>

static std::queue<std::string> changerStackEnQueue(std::stack<std::string> stack) {
    std::queue<std::string> queue;
    std::stack<std::string> stackInverse;
    while (!stack.empty()) {
        stackInverse.push(stack.top());
        stack.pop();
    }
    while (!stackInverse.empty()) {
        queue.push(stackInverse.top());
        stackInverse.pop();
    }
    return queue;
}
static void remplacerCaractere(std::string& formule, size_t pos, std::string aRemplacer, int valeur) {
    formule.replace(pos, aRemplacer.length(), std::to_string(valeur));
}
static std::string remplacer(std::string formule,Entite& attaquant, Entite& defenseur) {
    std::string formuleARenvoyer = formule;
    std::map<std::string, int> stringARemplacer = {
        {"u.ap", attaquant.getAttaque()},
        {"u.dp", attaquant.getDefence()},
        {"u.vi", attaquant.getVitesse()},
        {"c.ap", defenseur.getAttaque()},
        {"c.dp", defenseur.getDefence()},
        {"c.vi", defenseur.getVitesse()}
    };

    size_t position;
    for (std::map<std::string, int>::iterator it = stringARemplacer.begin(); it != stringARemplacer.end(); ++it) {
        const std::string& cle = it->first;
        int valeur = it->second;
        while ((position = formuleARenvoyer.find(cle)) != std::string::npos) {
            remplacerCaractere(formuleARenvoyer, position, cle, valeur);
        }
    }
    return formuleARenvoyer;
}
static std::stack<std::string> shuntingYard(std::string formuleMathematique) {
    std::stack<std::string> sortie;
    std::stack<char> pileOperateur;
    std::string nombre = "";
    if (formuleMathematique[0] == '-') {
        sortie.push("0");
    }
    for (std::string::iterator it = formuleMathematique.begin(); it != formuleMathematique.end(); it++) {
        if (isdigit(*it)) {
            nombre += *it;
        }
        else {
            if (!nombre.empty()) {
                sortie.push(nombre);
                nombre.clear();
            }
            if (*it == '+' || *it == '-') {
                while (!pileOperateur.empty() && pileOperateur.top() != '(') {
                    sortie.push(std::string(1, pileOperateur.top()));
                    pileOperateur.pop();
                }
                pileOperateur.push(*it);
            }
            else {
                if (*it == '*' || *it == '/') {
                    while (!pileOperateur.empty() && pileOperateur.top() != '(' && pileOperateur.top() != '+' && pileOperateur.top() != '-') {
                        sortie.push(std::string(1, pileOperateur.top()));
                        pileOperateur.pop();
                    }
                    pileOperateur.push(*it);
                }
                else {
                    if (*it == '(') {
                        pileOperateur.push(*it);
                    }
                    else {
                        if (*it == ')') {
                            while (!pileOperateur.empty() && pileOperateur.top() != '(') {
                                sortie.push(std::string(1, pileOperateur.top()));
                                pileOperateur.pop();
                            }
                            if (pileOperateur.empty()) {
                                Utilitaire::writeInLog("Il manque le caractere '('");
                                exit(EXIT_FAILURE);
                            }
                            pileOperateur.pop();
                        }
                        else {
                            if (!isspace(*it)) {
                                Utilitaire::writeInLog("Caractere invalide rencontre " + *it);
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                }
            }
        }
    }
    if (!nombre.empty()) {
        sortie.push(nombre);
    }

    while (!pileOperateur.empty()) {
        sortie.push(std::string(1, pileOperateur.top()));
        pileOperateur.pop();
    }
    return sortie;
}
static int calculeNotationPolonaiseInverse(std::queue<std::string> pileDeCalcule) {
    std::stack<int> sortie;
    while (!pileDeCalcule.empty()) {
        if (isdigit(pileDeCalcule.front()[0])) {
            sortie.push(std::stoi(pileDeCalcule.front().c_str()));
        }
        else {
            int b = sortie.top();
            sortie.pop();
            int a = sortie.top();
            sortie.pop();
            if (pileDeCalcule.front() == "+") {
                sortie.push(a + b);
            }
            else {
                if (pileDeCalcule.front() == "-") {
                    sortie.push(a - b);
                }
                else {
                    if (pileDeCalcule.front() == "*") {
                        sortie.push(a * b);
                    }
                    else {
                        if (pileDeCalcule.front() == "/") {
                            if (b == 0) {
                                Utilitaire::writeInLog("Division par 0");
                                exit(EXIT_FAILURE);
                            }
                            sortie.push((a / b));
                        }
                        else {
                            Utilitaire::writeInLog("Operateur invalide dans la pile NPI");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
        }
        pileDeCalcule.pop();
    }
    if (sortie.size() != 1) {
        Utilitaire::writeInLog("La sortie est completement vide ou est encore trops remplie");
        exit(EXIT_FAILURE);
    }
    return sortie.top();
}

int Utilitaire::applicationFormuleDeDegat(std::string formuleThéorique, Entite& attaquant, Entite& defenseur) {
    std::string formuleMathematique = remplacer(formuleThéorique, attaquant, defenseur);
    std::stack<std::string> pileDoperation = shuntingYard(formuleMathematique);
    std::queue<std::string> queueDeCalcule = changerStackEnQueue(pileDoperation);
    return calculeNotationPolonaiseInverse(queueDeCalcule);
}

int Utilitaire::getRandomInteger(int lowestValue,int highestValue) {
    if (!Utilitaire::randomGeneratorActivate) {
        Utilitaire::randomGeneratorActivate = true;
        std::random_device rd;
        Utilitaire::numberGenerator.seed(rd());
    }
    std::uniform_int_distribution<int> distribution{ lowestValue,highestValue };
    return distribution(numberGenerator);
}
int Utilitaire::getRandomInteger(int highestValue) {
    return getRandomInteger(0,highestValue);
}
int Utilitaire::getRandomInteger() {
    return getRandomInteger(0, 1000000);
}

static std::string dateAujourdhui() {
    std::time_t current_time = std::time(nullptr);
    std::tm local_time;
    localtime_s(&local_time, &current_time);
    char output[50];
    strftime(output, 50, "%d/%m/%y, %H:%M:%S", &local_time);
    return output;
}

void Utilitaire::nettoyerLog() {
    std::ofstream fichier{ NOM_FICHIER, std::ofstream::out | std::ofstream::trunc };
    fichier.close();
}
void Utilitaire::testHandler(bool test, const char* message, bool afficheSucces) {
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
        exit(EXIT_FAILURE);
    }
}
void Utilitaire::writeInLog(const char* message) {
    std::ofstream fichier{ NOM_FICHIER,std::ios::app };
    fichier << dateAujourdhui() + " , " + message + "\n";

}