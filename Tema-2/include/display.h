#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <string>

using namespace std;

void displayIntro();
void displayInstructions(string str);
void displayNewGenerationHelp();
void displayIncompleteSituation();
void displaySelection(string str);
void displayMissing(string, string);
void displayNotFound(string type, string name, int elems = 1, string type2="", string name2="");
void displayGenerationIncomplete();
void displayStatistics(int id, int counter, string compet, string lvl);
void displayNotAvailable(string str);
void displaySuccess(string str);
void displayExit();
void displayError(string);


#endif
