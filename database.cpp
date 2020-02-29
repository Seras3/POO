#include <iostream>
#include "database.h"
#include <string>
#include <fstream>

using namespace std;

DataBase::DataBase(){
    db_size = 100;
    last = 0;
    readed = 0;
    pers = new Person*[db_size];
    for(int i = 0; i < db_size ; i++)
        pers[i] = NULL;
}

DataBase::~DataBase(){
    last = 0;
    readed = 0;
    for(int i = 0 ; i < db_size; i++)
        delete[] pers[i];
    delete[] pers;
    db_size = 0;
}

void DataBase::addPerson(string name, int birth_year, char gender){
    if(last == db_size)
    {
        cout<<"\nThe data base is full.\n";
        return;
    }

    pers[last] = new Person;
    pers[last]->setName(name);
    pers[last]->setBirthYear(birth_year);
    pers[last]->setGender(gender);
    if(readed == 1)
    {
        cout<<"\n";
        cout<<pers[last]->getName();
        cout<<" has been successfully added! :) \n";
    }
    last++;
}


void DataBase::removePerson(string name){
    Person *aux;
    int ok = 0;
    for(int i=0; i < last; i++)
    {
        if(pers[i]->getName() == name)
        {
            aux = pers[i];
            pers[i] = pers[last-1];
            pers[last-1] = aux;
            pers[last-1] = NULL;
            last--;
            i--;
            ok = 1;
        }
    }
    if(ok == 0)
    {
        cout<<"\nNobody has the name "<< name <<", sorry.\n";
    }
    else
        cout<<"\nDone !\n";
}

void DataBase::removePerson(int birth_year){
    Person *aux;
    int ok = 0;
    for(int i=0; i < last; i++)
    {
        if(pers[i]->getBirthYear() == birth_year)
        {
            aux = pers[i];
            pers[i] = pers[last-1];
            pers[last-1] = aux;
            pers[last-1] = NULL;
            last--;
            i--;
            ok = 1;
        }
    }

    if(ok == 0)
    {
        cout<<"\nNobody has the birth year "<< birth_year <<", sorry.\n";
    }
    else
        cout<<"\nDone !\n";
}

void DataBase::removePerson(char gender){
    Person *aux;
    int ok = 0;
    for(int i=0; i < last; i++)
    {
        if(pers[i]->getGender() == gender)
        {
            aux = pers[i];
            pers[i] = pers[last-1];
            pers[last-1] = aux;
            pers[last-1] = NULL;
            last--;
            i--;
            ok = 1;
        }
    }
    if(ok == 0)
    {
        cout<<"\nNobody has the gender "<< gender <<", sorry.\n";
    }
    else
        cout<<"\nDone !\n";
}

void DataBase::printAlfByName(){
    Person *aux;
    for(int i=0; i < last-1; i++)
        for(int j=i+1; j < last; j++)
    {
        if(pers[i]->getName() > pers[j]->getName())
        {
            aux = pers[i];
            pers[i] = pers[j];
            pers[j] = aux;
        }
    }
    for(int i=0; i < last; i++)
        cout<<pers[i]->getName()<<" "<<pers[i]->getBirthYear()<<" "<<pers[i]->getGender()<<endl;
}

void DataBase::printByAge(){
    Person *aux;
    for(int i=0; i < last-1; i++)
        for(int j=i+1; j < last; j++)
    {
        if(pers[i]->getBirthYear() < pers[j]->getBirthYear())
        {
            aux = pers[i];
            pers[i] = pers[j];
            pers[j] = aux;
        }
    }
    for(int i=0; i < last; i++)
        cout<<pers[i]->getName()<<" "<<pers[i]->getBirthYear()<<" "<<pers[i]->getGender()<<endl;
}


void DataBase::readData(char file[100]){
    ifstream f (file);
    string name;
    int birth_year;
    char gender;

    while(f>>name>>birth_year>>gender)
        this->addPerson(name, birth_year, gender);

    this->readDone();
    f.close();
}

void DataBase::saveData(char file[100]){
    ofstream g (file);
    for(int i = 0; i < last; i++)
    {
        g<<(pers[i]->getName());
        g<<(" ");
        g<<(pers[i]->getBirthYear());
        g<<(" ");
        g<<(pers[i]->getGender());
        g<<("\n");
    }
    g.close();
}

void DataBase::readDone(){
    readed = 1;
}


