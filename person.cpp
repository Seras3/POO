#include <iostream>
#include "person.h"
#include <string>

using namespace std;

Person::Person(){
}

Person::Person(string name, int birth_year, char gender){
    this->name = name;
    this->birth_year = birth_year;
    this->gender = gender;
}

Person::~Person(){
}

void Person::setName(string name){
    this->name = name;
}

void Person::setBirthYear(int birth_year){
    this->birth_year = birth_year;
}

void Person::setGender(char gender){
    this->gender = gender;
}

string Person::getName(){
    return this->name;
}

int Person::getBirthYear(){
    return this->birth_year;
}

char Person::getGender(){
    return this->gender;
}




