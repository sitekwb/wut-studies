//
// Created by wojtek on 22.05.18.
//
#include "Teacher.hpp"
#include <iostream>
#include <iomanip>

using namespace std;
void Teacher::addGroup(int group){
    if(group<0 || group>99){
        throw InputException(longish);
    }
    for(auto it=groups.begin(); it!=groups.end(); it++){
        if(*it == group){
            throw InputException(existing);
        }
    }
    groups.push_back(group);

}

Teacher::Teacher(int teachId, std::string teachName, int teachSalary, std::string lang){
    id = teachId;
    language = lang;
    name = teachName;
    salary = teachSalary;
}

void Teacher::print(){
    cout<<"---|"<<setw(3)<<id<<"|"<<setw(30)<<name<<"|"<<setw(6)<<salary<<"|";
    cout<<setw(15)<<language<<"|---"<<endl;
}
string Teacher::getLang(){
    return language;
}
void Teacher::setLang(string lang){
    if(lang.length() >15){
        throw InputException(longish);
    }
    language = lang;
}