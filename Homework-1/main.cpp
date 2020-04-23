#include <iostream>
#include "person.h"
#include "database.h"
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;


void showInstructions()
{
    const int lenIns = 5;
    string instruct[lenIns];
    instruct[0] = "to take a look again at help list.";
    instruct[1] = "to see people ordered alphabetically by name.";
    instruct[2] = "to see them ordered by age.";
    instruct[3] = "to write somebody down here.";
    instruct[4] = "to delete everyone who has a specific (name / birth year / gender).";

    for(int i = 0; i < lenIns; i++)
    {
        cout<<"Press [";
        cout<<i;
        cout<<"] ";
        cout<<instruct[i]<<endl;
    }

    cout<<"Write 'exit' to quit this process."<<endl;

}

void verifFeedback(string user, DataBase &DB)
{
    string name;
    int birth_year;
    char gender;

    if(user == "0")
    {
        showInstructions();
    }
    else if(user == "1")
    {
        DB.printAlfByName();
    }
    else if(user == "2")
    {
        DB.printByAge();
    }
    else if(user == "3")
    {
        cout<<"So tell me about this person: \n";
        cout<<"Name: ";
        cin>>name;
        cout<<"Birth year: ";
        cin>>birth_year;
        cout<<"Gender: ";
        cin>>gender;
        DB.addPerson(name, birth_year, gender);
    }
    else if(user == "4")
    {
        cout<<"Do you want to delete by what? Type:[ name / birth year / gender ] \n";
        cin>> user;
        if(user == "name")
        {
            cout<<"Ok, so what's the name?\n";
            cin>>name;
            DB.removePerson(name);
        }
        else if(user == "birth year")
        {
            cout<<"Ok, so what's the birth year?\n";
            cin>>birth_year;
            DB.removePerson(birth_year);
        }
        else if(user == "gender")
        {
            cout<<"Ok, so what's the gender?\n";
            cin>>gender;
            DB.removePerson(gender);
        }
        else
        {
            cout<<"Please choose from our list next time. ;)\n";
        }
    }
    else if(user == "exit")
    {
        DB.saveData("people_db.in");
        cout<<"Thx for edit! Bye. :*";
    }
    else
    {
        cout<<"\nSorry, choose from help list only! \n";
    }
}


void menu(DataBase &DB)
{
    string user;
    cout<<"Hello stranger :D !\n\n";
    Sleep(1000);
    cout<<"That's our VIP list for the top secret party in BUCHAREST!\n";
    Sleep(1000);
    cout<<"Are you interested? [y\\n] :";
    user = getchar();
    if(user == "y")
    {
        cout<<"\nHah, cool ! XD \n";
        cout<<"You won the BIG PRIZE RIGHT NOW! \n";
        cout<<"You can add yourself or whoever you want in this list. \n";
        cout<<"You can also delete some other guys if you see somebody that you don't like.\n";
        cout<<"Make sure you see our list before you do this.\n";
        cout<<"All you need to do is to use these commands:\n";
        showInstructions();
        while(user != "exit")
        {
            cin>> user;
            verifFeedback(user, DB);
        }

    }
    else
    {
        cout<<"Meh, so I guess you have other plans... Bye :*";
    }
}

int main()
{
    DataBase DB;
    DB.readData("people_db.in");
    menu(DB);

    return 0;
}
