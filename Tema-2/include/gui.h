#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <fstream>
#include <string>
#include "generation.h"
#include "display.h"

using namespace std;

void strToName(string&);

class Gui {
    bool running;
    Generation last_generation;
protected:
    void initialization(int ord = 0);
    void selectInstruction();
    void loadNewGeneration();
    void evaluateStudent();
    void retryCourse();
    void readGeneration(string);  /// here
    void saveGeneration();  /// here
    void uploadGeneration();
    void uploadCountGenerations();
    void showLastStatistics();
    void showAllTimeStatistics();
    void showAllStudentsStatistics();
    void showAllStudentsStatisticsOverall();
    void showAllStudentsStatistics(string option);
    void showAllStudentsStatisticsOverall(string option);
    void showSpecificStudentStatistics();
    void showSpecificStudentStatisticsOverall();
    void retryProgram();
    bool completeGeneration();
    string getInput();
public:
    Gui( bool = true);
    ~Gui();
    void run();
};



#endif
