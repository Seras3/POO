#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <iostream>
#include "display.h"

using namespace std;

struct Test{
    string name;
    float grade;
};

struct EvaluationSheet{
    string student_name;
    string training_name;
    int course_type;
    string course_name;
    string test_name;
    float grade;
    string option1;
    string option2;
    EvaluationSheet(string st_name="", string tr_name="", int cr_type=0, string cr_name="", string op1="", string op2="", string ts_name="", float gr=0);
};


class Course {
protected:
    string name;
    unsigned int count_tests;
    Test* tests;
    float final_grade;
    bool promoted;
    bool complete;
    bool end_situation;
    int type;
public:
    Course(string = "", unsigned int = 0, Test* = nullptr);
    Course(Course&);
    virtual ~Course();

    virtual void calculateFinalGrade();
    bool checkComplete();
    bool isComplete();
    string getName();
    float getFinalGrade();
    void openSituation();
    bool isPromoted();
    bool isFinished();
    bool finalGradeOver3();
    void closeSituation();
    void displayFinished();
    virtual void updateGrade(EvaluationSheet& eval);
    virtual ostream& print(ostream&); /// optional afisare
    virtual void print();
    virtual int getType();
    virtual bool evalOption(EvaluationSheet& eval);
    virtual bool findOption(EvaluationSheet& eval);
    virtual void printFullName();

    static Course* createCourse(string name);
    static Course* createCourse(string name, string topic);
    static Course* createCourse(string name, string category, string language);


    friend ostream& operator<<(ostream&, Course&);
    Course& operator=(Course& );

    friend class CourseTopic;
    friend class DrivingTopic;
    friend class ProgrammingTopic;

};

class CourseTopic : public Course {
    string selected_topic;
public:
    CourseTopic(string name = "",
                unsigned int count_tests = 0,
                Test* tests = nullptr,
                string = "*unselected*");
    CourseTopic(CourseTopic&);
    ~CourseTopic();
    void calculateFinalGrade();
    ostream& print(ostream&);
    void setTopic(string topic, int tp = 2);
    void updateGrade(EvaluationSheet& eval);
    bool evalOption(EvaluationSheet& eval);
    bool findOption(EvaluationSheet& eval);
    int getType();
    void printFullName();
    void print();

    CourseTopic& operator=(Course&);
};

class DrivingTopic : public Course {
    string selected_vehicle;
public:
    DrivingTopic(string = "",
                 unsigned int = 0,
                 Test* = nullptr,
                 string = "*unselected*");
    DrivingTopic(DrivingTopic&);
    ~DrivingTopic();
    void calculateFinalGrade();
    ostream& print(ostream&);
    void setVehicle(string vehicle, int tp = 2);
    void updateGrade(EvaluationSheet& eval);
    int getType();
    bool evalOption(EvaluationSheet& eval);
    bool findOption(EvaluationSheet& eval);
    void printFullName();
    void print();

    DrivingTopic& operator=(Course&);
};

class ProgrammingTopic : public Course {
    string selected_category;
    string selected_language;
public:
    ProgrammingTopic(string name = "",
                     unsigned int count_tests = 0,
                     Test* tests = nullptr,
                     string = "*unselected*",
                     string = "*unselected*");
    ProgrammingTopic(ProgrammingTopic&);
    ~ProgrammingTopic();
    void calculateFinalGrade();
    ostream& print(ostream&);
    void setCategoryAndLanguage(string category, string language, int tp = 3);
    void updateGrade(EvaluationSheet& eval);
    int getType();
    bool evalOption(EvaluationSheet& eval);
    bool findOption(EvaluationSheet& eval);
    void printFullName();
    void print();

    ProgrammingTopic& operator=(Course&);
};


#endif // COURSE_H
