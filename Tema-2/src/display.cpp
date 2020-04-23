#include "../include/display.h"

void displayIntro()
{
    cout<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"||\t\t Welcome to Training Camp :D !\t\t\t\t  ||"<<endl;
    cout<<"||\t\t\t\t\t\t\t\t\t  ||"<<endl;
    cout<<"||\t It's a pleasure for us to have you here.\t\t\t  ||"<<endl;
    cout<<"|| Right now you're in the best place to commit results for your students,||"<<endl;
    cout<<"|| so give it a try after you check these instructions: \t\t  ||"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<endl;
}

void displayInstructions(string str)
{
    if( str == "intro" )
    {
        cout<<endl;
        cout<<"Introduce one of these numbers :"<<endl;
        cout<<"[0] - Instructions "<<endl;
        cout<<"[1] - Load new generation "<<endl;
        cout<<"[2] - Evaluate student "<<endl;
        cout<<"[3] - Display current situation "<<endl;
        cout<<"[4] - Retry course for a specific student "<<endl;
        cout<<"[5] - Retry program for a specific student "<<endl;
        cout<<"[6] - All time statistics "<<endl;
        cout<<"[7] - Last generation statistics "<<endl<<endl;
        cout<<"[9] - Exit "<<endl;
    }
    else if( str ==  "statistics" )
    {
        cout<<endl;
        cout<<"Introduce one of these numbers :"<<endl;
        cout<<"[1] - All students "<<endl;
        cout<<"[2] - Specific student "<<endl<<endl;
    }
    else if( str == "statistics_by")
    {
        cout<<endl;
        cout<<"Introduce one of these numbers :"<<endl;
        cout<<"[1] - By competence "<<endl;
        cout<<"[2] - By student " <<endl;
    }
    else if( str == "statistics_by_competence")
    {
        cout<<endl;
        cout<<"Introduce one of these numbers :"<<endl;
        cout<<"[1] - All competences "<<endl;
        cout<<"[2] - Specific competence "<<endl;
    }

    cout<<endl<<"Choose instruction: ";
}

void displayNewGenerationHelp()
{
    cout<<endl;
    cout<<"Now you should upload a file with your students."<<endl;
    cout<<"Check the format in README file."<<endl;
    cout<<"Write here (ex.) [C:\\absolute\\path\\of\\the\\file\\(file.extension)]: "<<endl;
}

void displayIncompleteSituation()
{
    cout<<endl;
    cout<<"Sorry, you must complete all the grades for this student. "<<endl;
}

void displayMissing(string name, string type)
{
    cout<<endl;
    cout<<"Sorry, we don't have "<< name << " " << type <<" available."<<endl;
}

void displayNotFound(string type, string name ,int elems , string type2, string name2)
{
    if(elems == 1)
        cout<<endl<<"Sorry, "<< type <<" "<< name <<" doesn't exists."<<endl;
    else if (elems == 2)
        cout<<endl<<"Sorry, "<< type <<" "<< name <<" or "<< type2 <<" "<< name2 <<" doesn't exists."<<endl;
}

void displayNotAvailable(string str)
{
    cout<<"Sorry, no " << str << " available."<<endl;
}

void displaySelection(string str)
{
    if( str == "student" )
    {
        cout<<"Enter the student name : ";
    }
    else if( str == "program" )
    {
        cout<<"Enter the program name : ";
    }
    else if( str == "course" )
    {
        cout<<"Enter the course name : ";
    }
    else if( str == "test" )
    {
        cout<<"Enter test name : ";
    }
    else if( str == "grade" )
    {
        cout<<"Grade : ";
    }
    else if( str == "option1" )
    {
        cout<<"Enter option1 : ";
    }
    else if( str == "option2" )
    {
        cout<<"Enter option2 : ";
    }
    else if( str == "retry_courses" )
    {
        cout<<"Choose one course from above to retry : ";
    }
    else if( str == "competence" )
    {
        cout<<"What competence are you looking for? : ";
    }
    else if( str == "level" )
    {
        cout<<"Choose the level [ low / medium / high ] : ";
    }
}

void displayStatistics(int id, int counter, string compet, string lvl)
{
    cout<<endl;
    cout<<"Generation no."<< id << endl;
    cout<<"Competence : "<< compet << endl;
    cout<<"Level : "<< lvl << endl;
    cout<<"Students available : "<< counter << endl;
}

void displaySuccess(string str)
{
    if( str == "sheet" )
    {
        cout<<"Grade has been successfully updated ! :D "<<endl;
    }
    else if( str == "end_situation" )
    {
        cout<<"End situation has been opened for tis program ! :D "<<endl;
    }
}

void displayGenerationIncomplete()
{
    cout<<"Sorry, actual generation is not finished. Complete all students grades. "<<endl;
}

void displayExit()
{
    cout<<"See you next time :D !"<<endl;
}

void displayError(string err)
{
    if( err == "bad_path")
    {
        cout<<"Sorry, I think you entered an invalid path or file."<<endl;
        cout<<"You can try again."<<endl;
    }
    else if( err == "bad_path_count_generations")
    {
        cout<<"Error: Bad path for count_generations. Check [data] folder ."<<endl;
    }
    else if( err == "invalid_main_input")
    {
        cout<<"Sorry, I think you should see the instructions."<<endl;
    }
    else if( err == "oops")
    {
        cout<<"Oops, something went wrong. Please try again !"<<endl;
    }
    else if( err == "invalid_grade")
    {
        cout<<"Sorry, grade must be a number between 0 and 10."<<endl;
    }
}
