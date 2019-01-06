//
// Created by wojtek on 15.04.18.
//
#include "../include/Teacher.hpp"

#define NAME_LENGTH 128

using namespace std;

Teacher::Teacher(std::string tName, std::string tMail){
    name = tName;
    mail=tMail;
    phone=0;
    checkMail(mail);
    checkName(name);
    isTeacher=true;
}

Teacher::Teacher(string tName, unsigned long tel){
    name = tName;
    phone=tel;
    mail="";
    checkName(name);
    checkPhone(phone);
    isTeacher=true;
}
Teacher::Teacher(string tName, string tMail, unsigned long tel){
    name = tName;
    mail=tMail;
    phone=tel;
    checkName(name);
    checkMail(mail);
    checkPhone(phone);
    isTeacher=true;
}

void Teacher::checkName(string &name)const{
    if (name.length() > NAME_LENGTH) {
        name.erase(NAME_LENGTH);
    }
}

string Teacher::getName(){
    return name;
}


Timetable *Teacher::getTimetablePtr(){
    return &timetable;
}
