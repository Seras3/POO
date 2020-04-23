#ifndef PERSON_H
#define PERSON_H
#include <string>

using namespace std;

class Person{
    private:
        string name;
        int birth_year;
        char gender;
    public:
        Person();
        Person(string name, int birth_year, char gender);
        ~Person();
        void setName(string name);
        string getName();
        void setBirthYear(int birth_year);
        int getBirthYear();
        void setGender(char gender);
        char getGender();
};

#endif

