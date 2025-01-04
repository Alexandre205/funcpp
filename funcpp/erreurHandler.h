#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>

#define NOM_FICHIER "log.txt"
void nettoyerLog();
void testHandler(bool test,const char* message,bool afficheSucces);
void writeInLog(const char* message);
