#include "../include/gui.h"

// This is for output names without underscore
void strToName(string& str)
{
    for(int i=0; i < str.length(); i++)
        if(str.compare(i,1,"_") == 0)
            str.replace(i,1," ");
}

Gui::Gui(bool running) : running{running} {}

Gui::~Gui() {}

void Gui::initialization(int ord)
{
    if(ord == 0)
    {
        Generation::setCountGenerations();
        if(Generation::getCountGenerations() > 0)
        {
            string from_file = "data/generations/generation_" + to_string(Generation::getCountGenerations()) + ".in";
            readGeneration(from_file);
            last_generation.setId(Generation::getCountGenerations());
            last_generation.checkAll();
            last_generation.isFinished();
            last_generation.closeSituations();
        }
    }
    else
    {
        if(Generation::getCountGenerations() > 0)
        {
            string from_file = "data/generations/generation_" + to_string(ord) + ".in";
            readGeneration(from_file);
            last_generation.setId(ord);
            last_generation.checkAll();
            last_generation.isFinished();
            last_generation.closeSituations();
        }
    }
}

void Gui::run()
{
    displayIntro();
    initialization(); /// incarca ultima generatie daca exista
    while(running)
    {
        selectInstruction();
    }
}


/// To update
bool Gui::completeGeneration()
{
    return last_generation.isFinished();
}


void Gui::loadNewGeneration()
{
    if(Generation::getCountGenerations() == 0 || completeGeneration())
    {
        string from_file;
        cin>>from_file;
        readGeneration(from_file);
        Generation::getCountGenerations()++;
        last_generation.setId(Generation::getCountGenerations());
        saveGeneration();
    }
    else
    {
        displayGenerationIncomplete();
    }
}

string Gui::getInput()
{
    string button;
    cin >> button;
    return button;
}

void Gui::readGeneration(string from_file)
{
    ifstream f (from_file);
    try
    {
        if(!f)
            throw "bad_path";
        f>>last_generation;
    }
    catch(const char* err)
    {
        if(err == "bad_path")
            displayError(err);
    }
    catch(...)
    {
        displayError("oops");
    }
    f.close();
}

void Gui::saveGeneration()
{
    uploadGeneration();
    uploadCountGenerations();   // comenteaza pentru dezactivare update count_generations
}

void Gui::uploadCountGenerations()
{
    /// Exceptii
    string to_file = Generation::getCountGenerationsPath();
    ofstream g (to_file);
    g<<Generation::getCountGenerations();
    g.close();
}

void Gui::uploadGeneration()
{
    string to_file = Generation::getStoreGenerationsPath() + to_string(Generation::getCountGenerations()) + ".in";
    ofstream g (to_file);
    g<<last_generation;
    g.close();
}

void Gui::evaluateStudent()
{
    EvaluationSheet eval;
    displaySelection("student");
    cin >> eval.student_name;
    if(last_generation.verifStudent(eval) == true)
    {
        last_generation.updateStudent(eval);
    }
    last_generation.isFinished();
}

void Gui::retryCourse()
{
    EvaluationSheet eval;
    displaySelection("student");
    cin >> eval.student_name;
    if(last_generation.findStudent(eval) == false)
    {
        displayNotFound("student", eval.student_name);
    }
    else
    {
        last_generation.showRetryableCourses(eval.student_name);
    }
}

void Gui::showAllTimeStatistics()   ///To_do
{
    displayInstructions("statistics");
    saveGeneration();
    string button = getInput();
    if(button == "1")
    {
        showAllStudentsStatisticsOverall();
    }
    else if(button == "2")
    {
        showSpecificStudentStatisticsOverall();
    }
    else
    {
        displayError("invalid_main_input");
    }
}

void Gui::showAllStudentsStatistics(string option)
{
    if(option == "by_competence")
    {
        displayInstructions("statistics_by_competence");
        string compet, lvl;
        string button = getInput();
        int counter = 0;
        if(button == "1")
        {
            if(!last_generation.showAllCompetenceStatistics())
                displayNotAvailable("competence");
        }
        else if(button == "2")
        {
            displaySelection("competence");
            compet = getInput();
            displaySelection("level");
            lvl = getInput();

            counter = last_generation.showCompetenceStatistics(compet, lvl);
        }
        else
        {
            displayError("invalid_main_input");
        }

    }
    else if(option == "by_student")
    {
        if(!last_generation.showStudentsStatistics())
        {
            displayNotAvailable("competence");
        }

    }

}

void Gui::showAllStudentsStatisticsOverall(string option)
{
    if(option == "by_competence")
    {
        displayInstructions("statistics_by_competence");
        string compet, lvl;
        string button = getInput();
        int counter = 0;
        bool found = false;
        if(button == "1")
        {
            for(int i = 1; i <= Generation::getCountGenerations(); i++)
            {
                initialization(i);
                if(last_generation.showAllCompetenceStatistics())
                    found = true;
            }
            if( found == false )
                displayNotAvailable("competence");
        }
        else if(button == "2")
        {
            displaySelection("competence");
            compet = getInput();
            displaySelection("level");
            lvl = getInput();

            for(int i = 1; i <= Generation::getCountGenerations(); i++)
            {
                initialization(i);
                last_generation.showCompetenceStatistics(compet, lvl);
            }
        }
        else
        {
            displayError("invalid_main_input");
        }

    }
    else if(option == "by_student")
    {
        bool found = false;
        for(int i = 1; i <= Generation::getCountGenerations(); i++)
        {
            initialization(i);
            if(last_generation.showStudentsStatistics())
            {
                found = true;
            }
        }
        if( found == false )
            displayNotAvailable("competence");

    }
}

void Gui::showAllStudentsStatistics()
{
    displayInstructions("statistics_by");
    string button = getInput();
    if(button == "1")
    {
        showAllStudentsStatistics("by_competence");
    }
    else if(button == "2")
    {
        showAllStudentsStatistics("by_student");
    }
    else
    {
        displayError("invalid_main_input");
    }
}

void Gui::showAllStudentsStatisticsOverall()
{
    displayInstructions("statistics_by");
    string button = getInput();
    if(button == "1")
    {
        showAllStudentsStatisticsOverall("by_competence");
    }
    else if(button == "2")
    {
        showAllStudentsStatisticsOverall("by_student");
    }
    else
    {
        displayError("invalid_main_input");
    }
}

void Gui::showSpecificStudentStatistics()
{
    displaySelection("student");
    string name = getInput();
    if(last_generation.findStudent(name))
    {
        if(!last_generation.showThisStudentStatistics(name))
        {
            displayMissing(name, "student_competences");
        }
    }
    else
    {
        displayNotFound("student", name);
    }

}

void Gui::showSpecificStudentStatisticsOverall()
{
    displaySelection("student");
    string name = getInput();
    bool foundS = false;
    bool foundComp = false;
    for(int i = 1 ; i <= Generation::getCountGenerations(); i++)
    {
        initialization(i);
        if(last_generation.findStudent(name))
        {
            if(last_generation.showThisStudentStatistics(name))
            {
               foundComp = true;
               cout<<"In generation no."<<last_generation.getID()<<endl<<endl;
            }
            foundS = true;
        }
    }
    if(foundS == false)
        displayNotFound("student", name);
    else
        if(foundComp == false)
            displayMissing(name, "student_competences");

}

void Gui::showLastStatistics()
{
    displayInstructions("statistics");
    string button = getInput();
    if(button == "1")
    {
        showAllStudentsStatistics();
    }
    else if(button == "2")
    {
        showSpecificStudentStatistics();
    }
    else
    {
        displayError("invalid_main_input");
    }

}

void Gui::retryProgram()
{
    displaySelection("student");
    string name = getInput();
    if(last_generation.findStudent(name))
    {
        displaySelection("program");
        string program = getInput();
        if(!last_generation.retryProgram(name, program))
        {
            displayNotFound("program", program);
            cout<<" Or maybe there are some grades below 3."<<endl;
        }
        else
            displaySuccess("end_situation");
    }
    else
    {
        displayNotFound("student", name);
    }

}


// Main manu selector
void Gui::selectInstruction()
{
    displayInstructions("intro");
    string button = getInput();
    if(button == "0")
    {
        selectInstruction();
    }
    else if(button == "1")
    {
        if( Generation::getCountGenerations() == 0 || completeGeneration() )
            displayNewGenerationHelp();
        loadNewGeneration();
    }
    else if(button == "2")  ///Evaluate student
    {
        evaluateStudent();
    }
    else if(button == "3")  ///Display current situation
    {
        last_generation.print();
    }
    else if(button == "4")  ///Retry course for a specific student
    {
        retryCourse();
    }
    else if(button == "5")  ///Retry program for a specific student
    {
        retryProgram();
    }
    else if(button == "6")  ///All time statistics
    {
        showAllTimeStatistics();
    }
    else if(button == "7")  ///Last generation statistics
    {
        showLastStatistics();
    }
    else if(button == "9")
    {
        displayExit();
        running = false;
        uploadGeneration();
    }
    else
    {
        displayError("invalid_main_input");
    }

}


