#include "../include/student.h"

Student::Student()
{
    name = "*blank*";
}

Student::Student(string name, TrainingProgram& training) : name{name}
{
    this->training = training;
}

Student::Student(Student& origin)
{
    *this = origin;
}

Student::~Student() {}

string Student::getName()
{
    return name;
}

string Student::getTrainingName()
{
    return training.getName();
}

void Student::updateTraining(EvaluationSheet& eval)
{
    training.updateCourse(eval);
}

bool Student::findProgram(EvaluationSheet& eval)
{
    return training.findProgram(eval);
}

bool Student::evalProgram(EvaluationSheet& eval)
{
    return training.evalProgram(eval);
}

bool Student::isFinished()
{
    training.checkComplete();
    return training.isFinished();
}

void Student::closeSituations()
{
    training.closeSituations();
}

void Student::fillCompetenceList(CompLevelList& cmpL)
{
    training.fillCompetenceList(cmpL);
}

bool Student::retryProgram(string program)
{
    return training.retryProgram(program);
}

void Student::showRetryableCourses()
{
    if(training.showRetryableCourses() == false)
        displayNotAvailable("courses");
    else
    {
        EvaluationSheet eval;
        displaySelection("retry_courses");
        cin >> eval.course_name;
        if( !training.retryCourse(eval) )
            displayNotFound("course", eval.course_name);
    }
}

int Student::getCountTrainings()
{
    return training.getCountTrainings();
}

int Student::showCompetenceStatistics(string comp, string lvl)
{
    return training.showCompetenceStatistics(comp, lvl);
}

bool Student::showThisStudentStatistics()
{
    return training.showThisStudentStatistics();
}

void Student::print()
{
    cout<<"Name : "<<name<<endl;
    training.print();
}

///-------------Operators-------------------------

Student& Student::operator=(Student& right_ob)
{
    name = right_ob.name;
    training = right_ob.training;
    return *this;
}

ostream& operator<<(ostream& os, Student& ob)
{
    int count_trainings = ob.getCountTrainings();
    os << ob.name << " " << count_trainings << "\n";
    os << ob.training;
    return os;
}

istream& operator>>(istream& is, Student& ob)
{
    is >> ob.name;
    string name;
    is >> name;
    ob.training = TrainingProgram::createProgram(name);
    ob.training.setName(name);
    return is;
}
