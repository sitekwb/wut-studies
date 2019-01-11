
#include "School.h"
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <Teacher.hpp>
#include <AdmWorker.hpp>

#define YEAR 2020

using namespace std;

void School::printStudents(std::ostream &str)
{
    if(studentsVector.empty()){
        throw InputException(emptyVector);
    }
    str << "\n";
    str << setw(3) << right << "ID" << "|| " << setw(30) << left << "Name or index number" << " || " << setw(3) << "Age" << " || ";
       cout << setw(15) << left << "Language" << " || " << "Group" << endl;

    for(auto it = studentsVector.begin(); it != studentsVector.end(); ++it)
    {
        (*it)->print(str);
    }
    str << endl;
}

void School::deleteStudent(int id)
{
    for(auto it= studentsVector.begin(); it != studentsVector.end(); ++it)
    {
        if((*it)->getID() == id)
        {
            delete *it;
            studentsVector.erase(it);
            return ;
        }
    }
    throw InputException(notFound);

}

void School::changeData(int id, int gr) //the chosen student gets its group changed to gr
{
    auto it= studentsVector.begin();
    for(; it != studentsVector.end(); ++it)
    {
        if((*it)->getID() == id)
        {
            (*it)->setGroup(gr);
            break;
        }
    }
    if(it==studentsVector.end()){
        throw InputException(notFound);
    }
}

void School::changeData(std::string lang, std::string newlang) //changes lang to newlang in students' data
{
    if(lang==""){
        throw InputException(notFound);
    }
    bool foundFlag=false;
    for(auto it = studentsVector.begin(); it != studentsVector.end() ; ++it)
    {
        if((*it)->getLang() == lang)
        {
            foundFlag = true;
            (*it)->setLang(newlang);
        }
    }
    for (auto it = workers.begin(); it!=workers.end(); it++){
        if((*it)->getLang() == lang)
        {
            foundFlag = true;
            (static_cast<Teacher *>(*it))->setLang(newlang);
        }
    }
    if(!foundFlag){
        throw InputException(notFound);
    }
}

Teacher *School::addTeacher(int id, std::string name, int salary, std::string language){
    if(id <= (workers.empty() ? 0: (workers.back()->getId())) || name.length()>30 || salary>99999 || salary<0 || language.length()>15){
        throw InputException(longish);
    }
    if(workers.size()==99){
        throw InputException(vectorSize);
    }
    Teacher *teacher = new Teacher(id, name, salary, language);
    workers.push_back(teacher);
    return teacher;
}
void School::addAdmWorker(int id, std::string name, int salary, int startYear){
    if(id <= workers.back()->getId() || name.length()>30 || salary>99999 || salary<0 || startYear<0
       || startYear > YEAR){
        throw InputException(longish);
    }
    if(workers.size()==99){
        throw InputException(vectorSize);
    }
    workers.push_back(new AdmWorker(id, name, salary, startYear));
}

void School::printWorkers() {
    if(workers.empty()){
        cout<<"Empty set of workers."<<endl;
        return ;
    }
    Worker::printHeader();
    for(auto it = workers.begin(); it != workers.end(); it++){
        (*it)->print();
    }
}

School::~School()
{
    for(auto it = studentsVector.begin(); it != studentsVector.end(); ++it)
    {
        delete *it;
    }
    for(auto it = workers.begin(); it!=workers.end(); ++it){
        delete *it;
    }
}

School& School::operator++() //overloaded function, each student's age gets increased by 1
{
	for(vector<StudentBase*>::iterator it = studentsVector.begin(); it != studentsVector.end(); ++it)
    {
        (*it)->increaseAge();
    }

    return *this;
}
