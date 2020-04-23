#include "../include/training_program.h"



/// ---------------------------- STRUCT ---------------------------------------------

CompLevel::CompLevel(string comp, string lvl)
{
    competence = comp;
    level = lvl;
}

CompLevel::CompLevel(const CompLevel& ob)
{
    *this = ob;
}

void CompLevel::print()
{
    cout<<competence<< " " <<level<<endl;
}

CompLevel& CompLevel::operator=(const CompLevel& ob)
{
    competence = ob.competence;
    level = ob.level;
    return *this;
}

bool CompLevel::operator==(const CompLevel& ob)
{
    if(competence == ob.competence && level == ob.level)
        return true;
    return false;
}

CompLevel CompLevelList::pop_back()
{
    CompLevel ob = this->back();
    vector<CompLevel>::pop_back();
    return ob;
}


void CompLevelList::print()
{
    vector<CompLevel>::iterator itr;
    for(itr = this->begin(); itr != this->end(); itr++)
        cout<<itr->competence << " " << itr->level<<endl;
}

void CompLevelList::add(CompLevel& ob)
{
    if(find(this->begin(), this->end(), ob) == this->end())
        this->push_back(ob);
}


/// ---------------------------- CLASS ----------------------------------------------

TrainingProgram::TrainingProgram(string competence, int count_courses, Course** courses, int count_trainings, TrainingProgram* trainings) :
                                 competence{competence}, count_courses{count_courses}, count_trainings{count_trainings}{

    final_grade = 0;
    level = "undefined";
    complete = false;
    promoted = false;
    try_again = false;
    end_situation = false;

    if(count_courses > 0)
    {
        this->courses = new Course*[count_courses];
        for(int i = 0; i < count_courses; i++)
            this->courses[i] = courses[i];
    }
    else
    {
        this->courses = nullptr;
    }

    if(count_trainings > 0)
    {
        this->trainings = new TrainingProgram[count_trainings];
        for(int i = 0; i < count_trainings; i++)
            this->trainings[i] = trainings[i];
    }
    else
    {
        this->trainings = nullptr;
    }

}

TrainingProgram::TrainingProgram(TrainingProgram& origin)
{
    *this = origin;
}

TrainingProgram::~TrainingProgram()
{
    if(courses)
        delete[] courses;
    if(trainings)
        delete[] trainings;
}


void TrainingProgram::calculateFinalGrade()
{

    final_grade = 0;
    for(int i = 0; i < count_courses; i++)
        final_grade += courses[i]->getFinalGrade();
    for(int i = 0; i < count_trainings; i++)
        final_grade += trainings[i].getFinalGrade();
    final_grade /= count_courses + count_trainings;
    final_grade = int(final_grade*100)/float(100);

    if(final_grade >= 5)
        promoted = true;
    if( 5<= final_grade && final_grade < 7 )
        level = "low";
    else if ( 7 <= final_grade && final_grade < 9)
        level = "medium";
    else if ( 9 <= final_grade)
        level = "high";
}

float TrainingProgram::getFinalGrade()
{
    return final_grade;
}

void TrainingProgram::fillCompetenceList(CompLevelList& cmpL)
{
    CompLevel ob;
    ob.competence = competence;
    ob.level = level;
    for(int i = 0; i < count_trainings; i++)
        trainings[i].fillCompetenceList(cmpL);

    if(level != "undefined")
        cmpL.add(ob);
}

bool TrainingProgram::isComplete()
{
    return complete;
}

bool TrainingProgram::checkComplete()
{
    int ok = 1;
    for(int i = 0; i < count_courses && ok == 1; i++)
        if(!(courses[i]->isComplete()||courses[i]->checkComplete()))
            ok = 0;
    for(int i = 0; i < count_trainings && ok == 1; i++)
        if(!(trainings[i].isComplete()||trainings[i].checkComplete()))
            ok = 0;
    if(ok)
    {
        calculateFinalGrade();
        complete = true;
    }
    else
        complete = false;
    return complete;

}


void TrainingProgram::endSituation()
{
    end_situation = true;
}

void TrainingProgram::closeSituations()
{
    if(isComplete())
        end_situation = true;
    for(int i = 0; i < count_courses; i++)
        if(courses[i]->isComplete())
            courses[i]->closeSituation();
    for(int i = 0; i < count_trainings; i++)
        trainings[i].closeSituations();
}

bool TrainingProgram::allCoursesGradesOver3()
{
    for(int i = 0; i < count_courses; i++)
        if(!courses[i]->finalGradeOver3())
            return false;
    return true;
}

bool TrainingProgram::retryProgram(string program)
{
    bool found = false;
    if( allCoursesGradesOver3() && competence == program )
    {
        for(int i = 0; i < count_courses; i++)
            courses[i]->openSituation();
        found = true;
    }
    for(int i = 0; i < count_trainings; i++)
        found = trainings[i].retryProgram(program) || found;
    return found;
}

bool TrainingProgram::showRetryableCourses()
{
    bool found = false;
    for(int i = 0; i < count_courses; i++)
        if(courses[i]->isPromoted() && courses[i]->isFinished())
        {
            found = true;
            courses[i]->printFullName();
            cout<<endl;
        }
    for(int i = 0; i < count_trainings; i++)
        found = trainings[i].showRetryableCourses() || found;
    return found;
}

bool TrainingProgram::retryCourse(EvaluationSheet& eval)
{
    bool found = false;
    if(findCourse(eval))
    {
        found = true;
        if(eval.course_type == 1)
        {
            for(int i = 0; i < count_courses; i++)
                if(courses[i]->getName() == eval.course_name && courses[i]->isComplete())
                {
                    courses[i]->openSituation();
                }
        }
        if(eval.course_type == 2)
        {
            displaySelection("option1");
            cin>>eval.option1;
            for(int i = 0; i < count_courses; i++)
                if(courses[i]->getName() == eval.course_name && courses[i]->isComplete() && courses[i]->findOption(eval))
                {
                    courses[i]->openSituation();
                }
        }
        else if(eval.course_type == 3)
        {
            if( eval.option1 == "")
            {
                displaySelection("option1");
                cin>>eval.option1;
            }
            if( eval.option2 == "")
            {
                displaySelection("option2");
                cin>>eval.option2;
            }
            for(int i = 0; i < count_courses; i++)
                if(courses[i]->getName() == eval.course_name && courses[i]->isComplete() && courses[i]->findOption(eval))
                {
                    courses[i]->openSituation();
                }
        }
    }
    for(int i = 0; i < count_trainings; i++)
        found = trainings[i].retryCourse(eval) || found ;
    return found;

}


void TrainingProgram::print()
{
    cout<<endl<<"\t"<<"Program name : "<<competence<<endl;
    if(isComplete()||checkComplete())
    {
        calculateFinalGrade();
        cout<<"\t"<<"level : "<<level<<endl;
        if(promoted)
        {
            cout<<"\t"<<"Yeey, this student has graduate this program!"<<endl;
            cout<<"\t"<<"His final grade is : "<<final_grade<<endl;
        }
        else
        {
            cout<<"\t"<<"Oh... this student didn't do so well at this program."<<endl;
            cout<<"\t"<<"His final grade is : "<<final_grade<<endl;
        }
        displayFinished();
    }
    Course *crs;
    for(int i = 0; i < count_courses; i++)
    {
        crs = courses[i];
        crs->print();
    }
    for(int i = 0; i < count_trainings; i++)
        trainings[i].print();
}

bool TrainingProgram::showThisStudentStatistics()
{
    bool found = false;
    if(level != "undefined")
    {
        found = true;
        cout<<"Competence : "<<competence<<" | Level : "<<level<<endl;
    }
    for(int i = 0; i < count_trainings; i++)
        found = trainings[i].showThisStudentStatistics() || found;
    return found;
}

int TrainingProgram::showCompetenceStatistics(string comp, string lvl)
{
    int counter = 0;
    if(competence == comp && level == lvl)
    {
        counter = 1;
    }
    for(int i = 0; i < count_trainings; i++)
    {
        counter += trainings[i].showCompetenceStatistics(comp, lvl);
    }
    return counter;
}

void TrainingProgram::updateCourse(EvaluationSheet& eval)
{
    if(competence == eval.training_name)
    {
        for(int i = 0; i < count_courses; i++)
            if(eval.course_name == courses[i]->getName())
            {
                courses[i]->updateGrade(eval);
            }
    }
    for(int i = 0; i < count_trainings; i++)
        trainings[i].updateCourse(eval);

}

bool TrainingProgram::findCourse(EvaluationSheet& eval)
{
    for(int i = 0; i < count_courses; i++)
        if(courses[i]->getName() == eval.course_name)
        {
            eval.course_type = courses[i]->getType();
            return true;
        }
    return false;
}

void TrainingProgram::displayFinished()
{
    if(end_situation == true)
        cout<< "\t" << "Program situation is closed."<<endl;
    else
        cout<< "\t" << "Program situation is not closed."<<endl;
    cout<<endl;
}

bool TrainingProgram::isFinished()
{
    for(int i = 0; i < count_courses; i++)
        if(!courses[i]->isFinished())
            return false;
    for(int i = 0; i < count_trainings; i++)
        if(!trainings[i].isFinished())
            return false;
    return true;
}


bool TrainingProgram::evalCourse(EvaluationSheet& eval)
{
    if(findCourse(eval) == false)
    {
        displayNotFound("course", eval.course_name);
        return false;
    }

    bool found = false;
    bool foundOpt = false;
    for(int i = 0; i < count_courses && found == false; i++)
        if(courses[i]->getName() == eval.course_name)
        {
            if(eval.course_type == 1)
            {
                found = courses[i]->evalOption(eval);
                foundOpt = courses[i]->findOption(eval);
            }
            if(eval.course_type == 2)
            {
                if(eval.option1 == "")
                {
                    displaySelection("option1");
                    cin >> eval.option1;
                }
                foundOpt = courses[i]->findOption(eval);
                found = courses[i]->evalOption(eval);
            }
            else if(eval.course_type == 3)
            {
                if(eval.option1 == "")
                {
                    displaySelection("option1");
                    cin >> eval.option1;
                }
                if(eval.option2 == "")
                {
                    displaySelection("option2");
                    cin >> eval.option2;
                }
                foundOpt = courses[i]->findOption(eval);
                found = courses[i]->evalOption(eval);
            }
        }
    if(foundOpt == false)
    {
        displayNotFound("option in course",eval.course_name);
    }
    return found;


}


bool TrainingProgram::findProgram(EvaluationSheet& eval)
{
    bool found = false;
    if(competence == eval.training_name)
    {
        return true;
    }
    for(int i = 0; i < count_trainings && found == false; i++)
    {
        found = trainings[i].findProgram(eval);
    }
    return found;
}


bool TrainingProgram::evalProgram(EvaluationSheet& eval)
{
    if(findProgram(eval) == false)
    {
        displayNotFound("program", eval.training_name);
        return false;
    }

    bool found = false;
    if(competence == eval.training_name)
    {
        if(eval.course_name == "")
        {
            displaySelection("course");
            cin >> eval.course_name;
        }
        found = evalCourse(eval);
    }
    for(int i = 0; i < count_trainings && found == false; i++)
        found = trainings[i].evalProgram(eval);

    return found;
}

int TrainingProgram::getCountTrainings(int count)
{
    for(int i = 0; i < count_trainings; i++)
        count +=  trainings[i].getCountTrainings();
    return count;
}

string TrainingProgram::getName()
{
    return competence;
}

void TrainingProgram::setName(string name)
{
    competence = name;
}


/// ------------------- Operators --------------------------------------------

TrainingProgram& TrainingProgram::operator=(TrainingProgram& origin)
{
    competence = origin.competence;
    level = origin.level;
    count_courses = origin.count_courses;
    count_trainings = origin.count_trainings;
    final_grade = origin.final_grade;
    promoted = origin.promoted;
    try_again = origin.try_again;
    end_situation = origin.end_situation;

    if(count_courses > 0)
    {
        courses = new Course*[count_courses];
        for(int i = 0; i < count_courses; i++)
            courses[i] = origin.courses[i];
    }

    if(count_trainings > 0)
    {
        trainings = new TrainingProgram[count_trainings];
        for(int i = 0; i < count_trainings; i++)
            trainings[i] = origin.trainings[i];
    }
    return *this;
}


TrainingProgram& TrainingProgram::createProgram(string name)
{
    if( name == "Financier" )
    {
        int counts_c = 2;
        Course** crs =  new Course*[counts_c];
        crs[0] = Course::createCourse("Mathematics", "Algebra");
        crs[1] = Course::createCourse("Finance");
        TrainingProgram* tp = new TrainingProgram(name, counts_c, crs);
        return *tp;
    }
    else if( name == "Manager" )
    {
        int counts_c = 3;
        Course** crs =  new Course*[counts_c];
        crs[0] = Course::createCourse("Human_resources");
        crs[1] = Course::createCourse("Finance");
        crs[2] = Course::createCourse("Language", "English");
        TrainingProgram* tp = new TrainingProgram(name, counts_c, crs);
        return *tp;
    }
    else if( name == "Programmer" )
    {
        int counts_c = 5;
        Course** crs = new Course*[counts_c];
        crs[0] = Course::createCourse("Mathematics", "Algebra");
        crs[1] = Course::createCourse("Mathematics", "Geometry");
        crs[2] = Course::createCourse("Mathematics", "Analysis");
        crs[3] = Course::createCourse("Programming", "OOP", "C++");
        crs[4] = Course::createCourse("Language", "English");
        TrainingProgram* tp = new TrainingProgram(name, counts_c, crs);
        return *tp;
    }
    else if( name == "Developer_team_manager" )
    {
        int counts_c = 2;
        int counts_t = 1;
        TrainingProgram* tr = &createProgram("Manager");
        Course** crs = new Course*[counts_c];
        crs[0] = Course::createCourse("Programming", "OOP", "C++");
        crs[1] = Course::createCourse("NLP_communication");
        TrainingProgram* tp = new TrainingProgram(name, counts_c, crs, counts_t, tr);
        return *tp;
    }
    else if( name == "Driver" )
    {
        int counts_c = 2;
        Course** crs = new Course*[counts_c];
        crs[0] = Course::createCourse("Driving_legislation");
        crs[1] = Course::createCourse("Practical_car_driving", "Skoda");
        TrainingProgram* tp = new TrainingProgram(name, counts_c, crs);
        return *tp;
    }
    else if( name == "Truckers_team_manager" )
    {
        int counts_c = 2;
        int counts_t = 1;
        TrainingProgram* tr = &createProgram("Manager");
        Course** crs = new Course*[counts_c];
        crs[0] = Course::createCourse("Language", "Turkish");
        crs[1] = Course::createCourse("Driving_legislation");
        TrainingProgram* tp = new TrainingProgram(name, counts_c, crs, counts_t, tr);
        return *tp;
    }
    else
    {
        displayMissing(name, "program");
        TrainingProgram* tp = new TrainingProgram("notFound");
        return *tp;
    }
}

ostream& operator<<(ostream& os, TrainingProgram& ob)
{
    os<< "\t" << ob.competence << " " << ob.count_courses << "\n";
    for(int i = 0; i < ob.count_courses; i++)
        os << *(ob.courses[i]);
    for(int i = 0; i < ob.count_trainings; i++)
        os << ob.trainings[i];
    return os;
}

