#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>
#include "training_program.h"

using namespace std;

class Student {
    string name;
    TrainingProgram training;
public:
    Student();
    Student(string name , TrainingProgram& training);
    Student(Student&);
    ~Student();

    string getName();
    string getTrainingName();
    void updateTraining(EvaluationSheet& eval);
    bool evalProgram(EvaluationSheet& eval);
    bool findProgram(EvaluationSheet& eval);
    bool isFinished();
    bool showThisStudentStatistics();
    int showCompetenceStatistics(string compet, string lvl);
    void showRetryableCourses();
    int getCountTrainings();
    void retryCourse();
    void print();
    void fillCompetenceList(CompLevelList& cmpL);
    void closeSituations();
    bool retryProgram(string program);


    Student& operator=(Student&);
    friend ostream& operator<<(ostream& , Student& );
    friend istream& operator>>(istream& , Student& );
};

#endif
