#include "../include/course.h"

/// ------------  EvaluationSheet --------------------------------------------------------------------------

EvaluationSheet::EvaluationSheet(string st_name, string tr_name, int cr_type, string cr_name, string op1, string op2, string ts_name, float gr)
{
    student_name = st_name;
    training_name = tr_name;
    course_type = cr_type;
    course_name = cr_name;
    option1 = op1;
    option2 = op2;
    test_name = ts_name;
    grade = gr;
}


/// ------------- Course -----------------------------------------------------------------------------------

Course::Course(string name, unsigned int count_tests, Test* tests) :
    name{name}, count_tests{count_tests}
{
    final_grade = 0;
    promoted = false;
    complete = false;
    end_situation = false;
    type = 1;

    if(count_tests > 0)
    {
        this->tests = new Test[count_tests];
        for(int i = 0; i < count_tests; i++)
        {
            this->tests[i] = tests[i];
        }
    }
}

Course::Course(Course& origin)
{
    name = origin.name;
    count_tests = origin.count_tests;
    final_grade = origin.final_grade;
    promoted = origin.promoted;
    end_situation = origin.end_situation;

    if(count_tests > 0)
    {
        tests = new Test[count_tests];
        for(int i = 0; i < count_tests; i++)
        {
            tests[i] = origin.tests[i];
        }
    }
}

Course::~Course()
{
    if(tests)
        delete[] tests;
}


void Course::calculateFinalGrade()
{
    if( name == "NLP_communication" )
    {
        float grade_speaking = 0;
        bool over5 = true;
        for(int i = 0; i < count_tests ; i++)
        {
            if(tests[i].name == "NLP_speaking")
            {
                grade_speaking = tests[i].grade;
            }
            else if( tests[i].grade < 5 )
            {
                over5 = false;
            }
        }
        if( over5 )
        {
            final_grade = grade_speaking;
            final_grade = int(final_grade*100)/float(100);
        }
        else
            final_grade = 1;
    }
    else if( name == "Human_resources" )
    {
        float lowest_grade = 99;
        for(int i = 0; i < count_tests; i++)
        {
            final_grade += tests[i].grade;
            if( lowest_grade > tests[i].grade )
                lowest_grade = tests[i].grade;
        }
        final_grade -= lowest_grade;
        final_grade /= count_tests - 1;
        final_grade = int(final_grade*100)/float(100);
    }
    else
    {
        for(int i = 0; i < count_tests; i++)
            final_grade += tests[i].grade;
        final_grade /= count_tests;
        final_grade = int(final_grade*100)/float(100);
    }

    if(final_grade >= 5)
            promoted = true;
        else
            promoted = false;
}

void Course::displayFinished()
{
    if(end_situation == false)
        cout<<"\t\t" << "Course situation is not closed."<<endl;
    else
        cout<<"\t\t" << "Course situation is closed."<<endl;
    cout<<endl;
}

float Course::getFinalGrade()
{
    return final_grade;
}

bool Course::isComplete()
{
    return complete;
}

void Course::openSituation()
{
    end_situation = false;
}

bool Course::checkComplete()
{
    int ok = 1;
    for(int i = 0; i < count_tests && ok == 1; i++)
        if(tests[i].grade == 0)
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

void Course::closeSituation()
{
    end_situation = true;
}

ostream& Course::print(ostream& os)
{
    os << "\t\t" << type << " " << name << " " << count_tests<< "\n";
    for(int i = 0; i < count_tests; i++)
        os<< "\t\t\t" << tests[i].name << " " << tests[i].grade << "\n";
    return os;
}

void Course::updateGrade(EvaluationSheet& eval)
{
    for(int i = 0; i < count_tests; i++)
        if(tests[i].name == eval.test_name)
        {
            tests[i].grade = eval.grade;
        }
    /// UPDATEAZA TOATE TESTELE CARE AU NUMELE test_name
}

bool Course::findOption(EvaluationSheet& eval)
{
    return true;
}

bool Course::evalOption(EvaluationSheet& eval)
{
    bool found = false;
    displaySelection("test");
    cin >> eval.test_name;
    for(int i = 0; i < count_tests && found == false; i++)
        if(tests[i].name == eval.test_name)
            found = true;
    if(found == true)
    {
        displaySelection("grade");
        cin >> eval.grade;
        if(eval.grade < 0 || eval.grade > 10 )
        {
            displayError("invalid_grade");
            found = false;
        }
        if(found == true)
        {
            displaySuccess("sheet");
        }
    }
    return found;
}

int Course::getType()
{
    return type;
}

bool Course::isPromoted()
{
    return promoted;
}

string Course::getName()
{
    return name;
}

Course* Course::createCourse(string name)
{
    int counts;
    Test* tests;
    if( name == "Finance" )
    {
        counts = 2;
        tests = new Test[counts];
        for(int i = 0; i < counts; i++)
            tests[i].grade = 0;
        tests[0].name = "Accountancy_evaluation";
        tests[1].name = "Applications_in_negotiation";
        Course* crs = new Course(name, counts, tests);
        return crs;
    }
    else if( name == "Human_resources" )
    {
        counts = 4;
        tests = new Test[counts];
        for(int i = 0; i < counts; i++)
            tests[i].grade = 0;
        tests[0].name = "Soft_skills_evaluation";
        tests[1].name = "Team_leading_test";
        tests[2].name = "Practice_of_public_speaking";
        tests[3].name = "Team_work_&_communication_contest";
        Course* crs = new Course(name, counts, tests);
        return crs;
    }
    else if( name == "NLP_communication" )
    {
        counts = 4;
        tests = new Test[counts];
        for(int i = 0; i < counts; i++)
            tests[i].grade = 0;
        tests[0].name = "NLP_writing";
        tests[1].name = "NLP_speaking";
        tests[2].name = "NLP_verification";
        tests[3].name = "NLP_progress";
        Course* crs = new Course(name, counts, tests);
        return crs;
    }
    else if( name == "Driving_legislation" )
    {
        counts = 2;
        tests = new Test[counts];
        for(int i = 0; i < counts; i++)
            tests[i].grade = 0;
        tests[0].name = "Traffic_situations";
        tests[1].name = "Driving_theory";
        Course* crs = new Course(name, counts, tests);
        return crs;
    }
    else if( name == "Mathematics" )
    {
        counts = 4;
        tests = new Test[counts];
        for(int i = 0; i < counts; i++)
            tests[i].grade = 0;
        tests[0].name = "Math_introduction_test";
        tests[1].name = "Math_accumulation_test";
        tests[2].name = "Math_theory_test";
        tests[3].name = "Math_final_evaluation";
        Course* crs = new Course(name, counts, tests);
        return crs;
    }
    else if( name == "Programming" )
    {
        counts = 3;
        tests = new Test[counts];
        for(int i = 0; i < counts; i++)
            tests[i].grade = 0;
        tests[0].name = "Syntax_understanding";
        tests[1].name = "Mid_project";
        tests[2].name = "Final_exam";
        Course* crs = new Course(name, counts, tests);
        return crs;
    }
    else if( name == "Language" )
    {
        counts = 2;
        tests = new Test[counts];
        for(int i = 0; i < counts; i++)
            tests[i].grade = 0;
        tests[0].name = "Speaking";
        tests[1].name = "Writing";
        Course* crs = new Course(name, counts, tests);
        return crs;
    }
    else if( name == "Practical_car_driving" )
    {
        counts = 2;
        tests = new Test[counts];
        for(int i = 0; i < counts; i++)
            tests[i].grade = 0;
        tests[0].name = "Parking_skills";
        tests[1].name = "Traffic_driving";
        Course* crs = new Course(name, counts, tests);
        return crs;
    }
    else
    {
        displayMissing(name, "course");
        Course* crs = new Course("notFound");
        return crs;
    }
}

Course* Course::createCourse(string name, string topic)
{
    if(name == "Mathematics")
    {
        Course *c = Course::createCourse(name);
        Course *ct = new CourseTopic;
        *ct = *c;
        static_cast<CourseTopic*>(ct)->setTopic(topic);
        delete c;
        return ct;
    }
    else if(name == "Language")
    {
        Course *c = Course::createCourse(name);
        Course *ct = new CourseTopic;
        *ct = *c;
        static_cast<CourseTopic*>(ct)->setTopic(topic);
        delete c;
        return ct;
    }
    else if(name == "Practical_car_driving")
    {
        Course* c = Course::createCourse(name);
        Course* dt = new DrivingTopic;
        *dt = *c;
        static_cast<DrivingTopic*>(dt)->setVehicle(topic);
        delete c;
        return dt;
    }
    else
    {
        displayMissing(name, "course");
        Course* ct = new Course("notFound");
        return ct;
    }
}

Course* Course::createCourse(string name, string category, string language)
{
    if(name == "Programming")
    {
        Course* c = Course::createCourse(name);
        Course* pt = new ProgrammingTopic;
        *pt = *c;
        static_cast<ProgrammingTopic*>(pt)->setCategoryAndLanguage(category, language);
        delete c;
        return pt;
    }
    else
    {
        displayMissing(name, "course");
        Course* pt = new Course("notFound");
        return pt;
    }
}

bool Course::finalGradeOver3()
{
    if(final_grade >= 3)
        return true;
    return false;
}

void Course::print()
{
    cout<<"\t\t"<<"Course name : " << name << endl;
    for(int i = 0; i < count_tests; i++)
        cout<< "\t\t\t" << tests[i].name << " : " << tests[i].grade << endl;
    if(isComplete())
    {
        cout<< "\t\t\t" << ">>> FINAL GRADE : " << getFinalGrade() << " ";
        if(isPromoted())
            cout<<"Promoted :D"<<endl;
        else
            cout<<"Failed :("<<endl;
    }
    displayFinished();
}

void Course::printFullName()
{
    cout<<name;
}

bool Course::isFinished()
{
    return end_situation;
}

ostream& operator<<(ostream& os, Course& ob)
{
    return ob.print(os);
}


Course& Course::operator=(Course& right_ob)
{
    name = right_ob.name;
    count_tests = right_ob.count_tests;
    final_grade = right_ob.final_grade;
    promoted = right_ob.promoted;
    end_situation = right_ob.end_situation;
    if(count_tests > 0)
    {
        tests = new Test[count_tests];
        for(int i = 0; i < count_tests; i++)
        {
            tests[i] = right_ob.tests[i];
        }
    }
    return *this;
}


/// --------------- COURSE TOPIC -----------------------------------------------------------------------

CourseTopic::CourseTopic(string name, unsigned int count_tests, Test* tests, string selected_topic) :
                         Course(name, count_tests, tests), selected_topic{selected_topic}{}

CourseTopic::CourseTopic(CourseTopic& origin) : Course(origin)
{
    selected_topic = origin.selected_topic;
}

CourseTopic::~CourseTopic(){}

void CourseTopic::calculateFinalGrade()
{
    /// mai adaug conditii si pentru celelalte cursuri
    final_grade = 0;
    if(name == "Mathematics")
    {
        for(int i = 0; i < count_tests; i++)
            final_grade += tests[i].grade;
        final_grade /= count_tests;

        if(final_grade >= 5)
            promoted = true;
    }
    else
        if(name == "Language")
    {
        for(int i = 0; i < count_tests; i++)
            final_grade += tests[i].grade;
        final_grade /= count_tests;

        if(final_grade >= 5)
            promoted = true;
    }
}

ostream& CourseTopic::print(ostream& os)
{
    os << "\t\t" << type << " " << name << " " << selected_topic << " " << count_tests << "\n";
    for(int i = 0; i < count_tests; i++)
        os<< "\t\t\t" << tests[i].name << " " << tests[i].grade << "\n";
    return os;
}

void CourseTopic::setTopic(string topic, int tp)
{
    selected_topic = topic;
    type = tp;
}

void CourseTopic::updateGrade(EvaluationSheet& eval)
{
    if(eval.option1 == selected_topic)
    {
        for(int i = 0; i < count_tests; i++)
            if(tests[i].name == eval.test_name)
            {
                tests[i].grade = eval.grade;
            }
    }
    /// UPDATEAZA TOATE TESTELE CARE AU NUMELE test_name
}

int CourseTopic::getType()
{
    return type;
}

bool CourseTopic::findOption(EvaluationSheet& eval)
{
    if(selected_topic == eval.option1)
        return true;
    return false;
}

bool CourseTopic::evalOption(EvaluationSheet& eval)
{
    if(findOption(eval) == false)
    {
        return false;
    }
    bool found = false;
    displaySelection("test");
    cin >> eval.test_name;
    for(int i = 0; i < count_tests && found == false; i++)
        if(tests[i].name == eval.test_name)
            found = true;
    if(found == true)
    {
        displaySelection("grade");
        cin >> eval.grade;
        if(eval.grade < 0 || eval.grade > 10 )
        {
            displayError("invalid_grade");
            found = false;
        }
        if(found == true)
        {
            displaySuccess("sheet");
        }
    }
    return found;
}

void CourseTopic::print()
{
    cout<<"\t\t"<<"Course name : " << name <<  endl;
    cout<<"\t\t"<<"Topic : " << selected_topic <<endl;
    for(int i = 0; i < count_tests; i++)
        cout<< "\t\t\t" << tests[i].name << " : " << tests[i].grade << endl;
    if(isComplete())
    {
        cout<< "\t\t\t" << ">>> FINAL GRADE : " << getFinalGrade() << " ";
        if(isPromoted())
            cout<<"Promoted :D"<<endl;
        else
            cout<<"Failed :("<<endl;
    }
    displayFinished();
}


void CourseTopic::printFullName()
{
    cout<<name<<" "<<selected_topic;
}


CourseTopic& CourseTopic::operator=(Course& origin)
{
    name = origin.name;
    count_tests = origin.count_tests;
    final_grade = origin.final_grade;
    promoted = origin.promoted;
    end_situation = origin.end_situation;
    if(count_tests > 0)
    {
        tests = new Test[count_tests];
        for(int i = 0; i < count_tests; i++)
        {
            tests[i] = origin.tests[i];
        }
    }
    return *this;
}


///------------------- Driving -------------------------------------------------------------------------

DrivingTopic::DrivingTopic(string name, unsigned int count_tests, Test* tests, string selected_vehicle) :
    Course(name, count_tests, tests), selected_vehicle{selected_vehicle}{}

DrivingTopic::DrivingTopic(DrivingTopic& origin)
{
    selected_vehicle = origin.selected_vehicle;
}

DrivingTopic::~DrivingTopic(){}

void DrivingTopic::calculateFinalGrade()
{
    final_grade = 0;
    for(int i = 0; i < count_tests; i++)
    {
        if(i == 0) // dupa nume le schimb dupa
            final_grade += tests[i].grade*0.2;
        if(i == 1)
            final_grade += tests[i].grade*0.3;
        if(i == 2)
            final_grade += tests[i].grade*0.5;

        final_grade = int(final_grade*100)/float(100);

        if(final_grade >= 5)
            promoted = true;
    }
}

void DrivingTopic::updateGrade(EvaluationSheet& eval)
{
    if(eval.option1 == selected_vehicle)
    {
        for(int i = 0; i < count_tests; i++)
            if(tests[i].name == eval.test_name)
            {
                tests[i].grade = eval.grade;
            }
    }
    /// UPDATEAZA TOATE TESTELE CARE AU NUMELE test_name
}


bool DrivingTopic::findOption(EvaluationSheet& eval)
{
    if(selected_vehicle == eval.option1)
        return true;
    return false;
}

bool DrivingTopic::evalOption(EvaluationSheet& eval)
{
    if(findOption(eval) == false)
    {
        return false;
    }
    bool found = false;
    displaySelection("test");
    cin >> eval.test_name;
    for(int i = 0; i < count_tests && found == false; i++)
        if(tests[i].name == eval.test_name)
            found = true;
    if(found == true)
    {
        displaySelection("grade");
        cin >> eval.grade;
        if(eval.grade < 0 || eval.grade > 10 )
        {
            displayError("invalid_grade");
            found = false;
        }
        if(found == true)
        {
            displaySuccess("sheet");
        }
    }
    return found;
}


int DrivingTopic::getType()
{
    return type;
}

ostream& DrivingTopic::print(ostream& os)
{
    os << "\t\t" << type << " " << name << " " << selected_vehicle << " " << count_tests << "\n";
    for(int i = 0; i < count_tests; i++)
        os<< "\t\t\t" << tests[i].name << " " << tests[i].grade << "\n";
    return os;
}

void DrivingTopic::print()
{
    cout<<"\t\t"<<"Course name : " << name <<  endl;
    cout<<"\t\t"<<"Vehicle : " << selected_vehicle <<endl;
    for(int i = 0; i < count_tests; i++)
        cout<< "\t\t\t" << tests[i].name << " : " << tests[i].grade << endl;
    if(isComplete())
    {
        cout<< "\t\t\t" << ">>> FINAL GRADE : " << getFinalGrade() << " ";
        if(isPromoted())
            cout<<"Promoted :D"<<endl;
        else
            cout<<"Failed :("<<endl;
    }
    displayFinished();
}

void DrivingTopic::printFullName()
{
    cout<<name<<" "<<selected_vehicle;
}

void DrivingTopic::setVehicle(string vehicle, int tp)
{
    selected_vehicle = vehicle;
    type = tp;
}

DrivingTopic& DrivingTopic::operator=(Course& origin)
{
    name = origin.name;
    count_tests = origin.count_tests;
    final_grade = origin.final_grade;
    promoted = origin.promoted;
    end_situation = origin.end_situation;
    if(count_tests > 0)
    {
        tests = new Test[count_tests];
        for(int i = 0; i < count_tests; i++)
        {
            tests[i] = origin.tests[i];
        }
    }
    return *this;
}


/// ----------------- Programming ------------------------------------------------------------------------

ProgrammingTopic::ProgrammingTopic(string name, unsigned int count_tests, Test* tests, string selected_category, string selected_language) :
    Course(name, count_tests, tests), selected_category{selected_category}, selected_language{selected_language} {}

ProgrammingTopic::ProgrammingTopic(ProgrammingTopic& origin)
{
    selected_category = origin.selected_category;
    selected_language = origin.selected_language;
}

ProgrammingTopic::~ProgrammingTopic(){}

void ProgrammingTopic::calculateFinalGrade()
{
    final_grade = 0;
    for(int i = 0; i < count_tests; i++)
    {
        if(i == 0) // dupa nume le schimb dupa
            final_grade += tests[i].grade*0.2;
        if(i == 1)
            final_grade += tests[i].grade*0.3;
        if(i == 2)
            final_grade += tests[i].grade*0.5;

        final_grade = int(final_grade*100)/float(100);

        if(final_grade >= 5)
            promoted = true;
    }
}

void ProgrammingTopic::updateGrade(EvaluationSheet& eval)
{
    if(eval.option1 == selected_category && eval.option2 == selected_language)
    {
        for(int i = 0; i < count_tests; i++)
            if(tests[i].name == eval.test_name)
            {
                tests[i].grade = eval.grade;
            }
    }
    /// UPDATEAZA TOATE TESTELE CARE AU NUMELE test_name
}

int ProgrammingTopic::getType()
{
    return type;
}

ostream& ProgrammingTopic::print(ostream& os)
{
    os << "\t\t" << type << " " << name << " " << selected_category << " " << selected_language << " " << count_tests << "\n";
    for(int i = 0; i < count_tests; i++)
        os<< "\t\t\t" << tests[i].name << " " << tests[i].grade << "\n";
    return os;
}

bool ProgrammingTopic::findOption(EvaluationSheet& eval)
{
    if(selected_category == eval.option1 && selected_language == eval.option2)
        return true;
    return false;
}

bool ProgrammingTopic::evalOption(EvaluationSheet& eval)
{
    if(findOption(eval) == false)
    {
        return false;
    }
    bool found = false;
    displaySelection("test");
    cin >> eval.test_name;
    for(int i = 0; i < count_tests && found == false; i++)
        if(tests[i].name == eval.test_name)
            found = true;
    if(found == true)
    {
        displaySelection("grade");
        cin >> eval.grade;
        if(eval.grade < 0 || eval.grade > 10 )
        {
            displayError("invalid_grade");
            found = false;
        }
        if(found == true)
        {
            displaySuccess("sheet");
        }
    }
    return found;
}

void ProgrammingTopic::print()
{
    cout<<"\t\t"<<"Course name : " << name <<  endl;
    cout<<"\t\t"<<"Category : " << selected_category << endl;
    cout<<"\t\t"<<"Language : " << selected_language << endl;
    for(int i = 0; i < count_tests; i++)
        cout<< "\t\t\t" << tests[i].name << " : " << tests[i].grade << endl;
    if(isComplete())
    {
        cout<< "\t\t\t" << ">>> FINAL GRADE : " << getFinalGrade() << " ";
        if(isPromoted())
            cout<<"Promoted :D"<<endl;
        else
            cout<<"Failed :("<<endl;
    }
    displayFinished();
}

void ProgrammingTopic::printFullName()
{
    cout<<name<<" "<<selected_category<<" "<<selected_language;
}


void ProgrammingTopic::setCategoryAndLanguage(string category, string language, int tp)
{
    selected_category = category;
    selected_language = language;
    type = tp;
}

ProgrammingTopic& ProgrammingTopic::operator=(Course& origin)
{
    name = origin.name;
    count_tests = origin.count_tests;
    final_grade = origin.final_grade;
    promoted = origin.promoted;
    end_situation = origin.end_situation;
    if(count_tests > 0)
    {
        tests = new Test[count_tests];
        for(int i = 0; i < count_tests; i++)
        {
            tests[i] = origin.tests[i];
        }
    }
    return *this;
}


///continuat si la restu


