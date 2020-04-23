#ifndef GENERATION_H
#define GENERATION_H
#include <string>
#include <vector>
#include "student.h"
#include "display.h"


using namespace std;

class Generation {
    static int count_generations;
    static const string count_generations_path;
    static const string store_generations_path;

    int id;
    int count_students;
    int limit_students;
    Student *students;
public:
    Generation(int = -1, int = 0, int = 255, Student* = nullptr);
    Generation(const Generation&);
    ~Generation();

    static void setCountGenerations();
    static string getStoreGenerationsPath();
    static string getCountGenerationsPath();
    static int& getCountGenerations(); /// de revazut referinta aia

    void updateStudent(EvaluationSheet& eval);
    bool findStudent(EvaluationSheet& eval);
    bool findStudent(string name);
    bool verifStudent(EvaluationSheet& eval);
    void setId(unsigned int);
    bool isFinished();
    int getID();
    bool showThisStudentStatistics(string name);
    bool showStudentsStatistics();
    int showCompetenceStatistics(string compet, string lvl);
    bool showAllCompetenceStatistics();
    void checkAll();
    void print();
    void closeSituations();
    void showRetryableCourses(string name);
    bool retryProgram(string name, string program);


    Generation& operator=(const Generation&);
    friend istream& operator>>(istream&, Generation&);
    friend ostream& operator<<(ostream&, Generation&);

};

#endif
