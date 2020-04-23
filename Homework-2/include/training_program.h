#ifndef TRAINING_PROGRAM_H
#define TRAINING_PROGRAM_H
#include <string>
#include <vector>
#include <algorithm>
#include "course.h"

using namespace std;

struct CompLevel{
    string competence;
    string level;
    CompLevel(string comp="", string lvl="");
    CompLevel(const CompLevel& ob);
    bool operator==(const CompLevel& ob);
    CompLevel& operator=(const CompLevel& ob);
    void print();
};

class CompLevelList : public vector<CompLevel>{
public:
    void print();
    void add(CompLevel& ob);
    CompLevel pop_back();
};


class TrainingProgram {
    string competence;
    string level;
    int count_courses;
    Course** courses;
    int count_trainings;
    TrainingProgram* trainings;
    float final_grade;
    bool complete;
    bool promoted;
    bool try_again;
    bool end_situation;
public:
    TrainingProgram(string = "undefined",
                    int count_courses = 0,
                    Course** = nullptr,
                    int count_trainings = 0,
                    TrainingProgram* = nullptr
                    );
    TrainingProgram(TrainingProgram&);
    ~TrainingProgram();

    string getName();
    void setName(string name);
    bool checkComplete();
    bool isComplete();
    bool isFinished();
    void calculateFinalGrade();
    void endSituation();
    void displayFinished();
    void fillCompetenceList(CompLevelList& cmpL);
    static TrainingProgram& createProgram(string name);
    float getFinalGrade();
    int getCountTrainings(int count = 1);
    void print();
    bool retryCourse(EvaluationSheet&eval);
    bool showThisStudentStatistics();
    int showCompetenceStatistics(string comp, string lvl);
    void closeSituations();
    bool showRetryableCourses();
    bool retryProgram(string program);
    bool allCoursesGradesOver3();
    void updateCourse(EvaluationSheet& eval);
    bool evalProgram(EvaluationSheet& eval);
    bool findProgram(EvaluationSheet& eval);
    bool findCourse(EvaluationSheet& eval);
    bool evalCourse(EvaluationSheet& eval);

    TrainingProgram& operator=(TrainingProgram&);
    friend ostream& operator<<(ostream& os, TrainingProgram&);
};



#endif // TRAINING_PROGRAM_H
