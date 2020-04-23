#include "../include/generation.h"
#include <fstream>
#include <iostream>

int Generation::count_generations;
const string Generation::count_generations_path = "data/count_generations.in";
const string Generation::store_generations_path = "data/generations/generation_";


Generation::Generation(int id, int count_students, int limit_students, Student* s) :
                        id{id}, count_students{count_students}, limit_students{limit_students}
{
    students = new Student[count_students];
    if(s)
    {
        for(int i = 0; i < count_students; i++)
        {
            students[i] = s[i];
        }
    }

}

Generation::Generation(const Generation& origin)
{
    *this = origin;
}

Generation::~Generation()
{
    if(students)
        delete []students;
}

int& Generation::getCountGenerations()
{
    return count_generations;
}

string Generation::getStoreGenerationsPath()
{
    return store_generations_path;
}

string Generation::getCountGenerationsPath()
{
    return count_generations_path;
}

void Generation::setId(unsigned int id)
{
    this->id = id;
}

void Generation::setCountGenerations()
{
    ifstream f (count_generations_path);
    try
    {
        if(!f)
            throw "bad_path_count_generations";
        f>>Generation::count_generations;
    }
    catch(const char* err)
    {
        displayError(err);
        /// save&exit()
    }
    catch(...)
    {
        displayError("oops");
        /// save&exit()
    }
    f.close();
}

void Generation::print()
{
    cout<<endl<<"This is generation no."<<id<<endl;
    if(isFinished())
        cout<<"Congrats, you can begin another generation!" << endl;
    else
        cout<<"This generation is not finished yet. " << endl;
    cout<<endl;

    for(int i = 0; i < count_students; i++)
        students[i].print();
}

int Generation::getID()
{
    return id;
}

void Generation::showRetryableCourses(string name)
{
    bool found = false;
    for(int i = 0; i < count_students && found == false; i++)
    {
        if(students[i].getName() == name)
        {
            found = true;
            students[i].showRetryableCourses();
        }
    }

}

bool Generation::showStudentsStatistics()
{
    bool found = false;
    cout << endl << "=> For generation no." << id << " <=" << endl;
    for(int i = 0; i < count_students; i++)
    {
        cout << students[i].getName() << endl;
        found = students[i].showThisStudentStatistics() || found;
        cout << endl;
    }
    return found;
}

bool Generation::showAllCompetenceStatistics()
{
    CompLevelList cmpL;
    CompLevel cmp;
    for(int i = 0; i < count_students; i++)
        students[i].fillCompetenceList(cmpL);


    if(cmpL.empty())
        return false;
    while(!cmpL.empty())
    {
        cmp = cmpL.pop_back();
        showCompetenceStatistics(cmp.competence, cmp.level);
    }
    return true;
}

bool Generation::retryProgram(string name, string program)
{
    for(int i = 0; i < count_students; i++)
        if(students[i].getName() == name)
            return students[i].retryProgram(program);
}

void Generation::updateStudent(EvaluationSheet& eval)
{
    bool found = false;
    for(int i = 0; i < count_students && found == false; i++)
        if(students[i].getName() == eval.student_name)
        {
            found = true;
            students[i].updateTraining(eval);
        }
}

int Generation::showCompetenceStatistics(string compet, string lvl)
{
    int count = 0;
    for(int i = 0; i < count_students; i++)
    {
        count += students[i].showCompetenceStatistics(compet,lvl);
    }
    displayStatistics(id, count, compet, lvl);
    return count;
}

bool Generation::findStudent(EvaluationSheet& eval)
{
    string name;
    for(int i = 0; i < count_students; i++)
    {
        name = students[i].getName();
        if(eval.student_name == name)
            return true;
    }
    return false;
}

bool Generation::findStudent(string name)
{
    for(int i = 0; i < count_students; i++)
    {
        if(students[i].getName() == name)
            return true;
    }
    return false;
}

bool Generation::showThisStudentStatistics(string name)
{
    for(int i = 0; i < count_students; i++)
    {
        if(students[i].getName() == name)
            return students[i].showThisStudentStatistics();
    }
}

bool Generation::verifStudent(EvaluationSheet& eval)
{
    bool found = false;

    if(findStudent(eval) == false)
    {
        displayNotFound("student", eval.student_name);
        return false;
    }

    for(int i = 0; i < count_students && found == false; i++)
        if(students[i].getName() == eval.student_name)
        {
            found = true;
            displaySelection("program");
            cin >> eval.training_name;
            return students[i].evalProgram(eval);
        }
}

void Generation::closeSituations()
{
    for(int i = 0; i < count_students; i++)
        students[i].closeSituations();
}

void Generation::checkAll()
{
    for(int i = 0; i < count_students; i++)
        students[i].isFinished();
}

bool Generation::isFinished()
{
    for(int i = 0; i < count_students; i++)
        if(!students[i].isFinished())
            return false;
    return true;
}

Generation& Generation::operator=(const Generation& origin)
{
    id = origin.id;
    count_students = origin.count_students;
    limit_students = origin.limit_students;
    if(count_students > 0)
    {
        students = new Student[count_students];
        for(int i = 0; i < count_students; i++)
            students[i] = origin.students[i];
    }
    return *this;
}

istream& operator>>(istream& is, Generation& ob)
{
    int count_sheets, count_trainings, count_courses, count_tests;
    bool valid_type;
    is >> ob.count_students >> ob.limit_students;
    ob.students = new Student[ob.count_students];
    for(int i = 0; i < ob.count_students; i++)
    {
        is>>ob.students[i];
    }
    is >> count_sheets;
    EvaluationSheet eval;
    for(int i = 0; i < count_sheets; i++)
    {
        is>>eval.student_name>>count_trainings;
        for(int j = 0; j < count_trainings; j++)
        {
            is>>eval.training_name>>count_courses;
            for(int k = 0; k < count_courses; k++)
            {
                valid_type = true;
                is>>eval.course_type>>eval.course_name;
                if(eval.course_type == 2)
                {
                    is>>eval.option1;
                }
                else if(eval.course_type == 3)
                {
                    is>>eval.option1>>eval.option2;
                }
                else if(eval.course_type != 1)
                {
                    cout<<"Sorry invalid course type"<<endl;
                    valid_type = false;
                }
                is>>count_tests;

                if(valid_type == true)
                {
                    for(int l = 0; l < count_tests; l++)
                    {
                        is>>eval.test_name>>eval.grade;
                        ob.updateStudent(eval);
                    }
                }
            }
        }
    }

    return is;
}

ostream& operator<<(ostream& os, Generation& ob)
{
    os << ob.count_students << " " << ob.limit_students<< '\n';
    for(int i = 0; i < ob.count_students; i++)
    {
        os << ob.students[i].getName() << " " << ob.students[i].getTrainingName() << '\n';
    }
    os << ob.count_students << "\n";
    for(int i = 0; i < ob.count_students; i++)
    {
        os << ob.students[i];
    }

}


