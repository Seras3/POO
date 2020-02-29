#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include "person.h"

using namespace std;

class DataBase{
    private:
        int db_size;
        int last;
        Person **pers;
        int readed;
    public:
        DataBase();
        ~DataBase();
        void addPerson(string name, int birth_year, char gender);
        void removePerson(string name);
        void removePerson(int birth_year);
        void removePerson(char gender);
        void printAlfByName();
        void printByAge();
        void readDone();
        void readData(char file[100]);
        void saveData(char file[100]);
};

#endif
