//
// Created by wojtek on 15.04.18.
//

#ifndef PROJECT_TWO_PERSON_HPP
#define PROJECT_TWO_PERSON_HPP
#include <string>


class Person{
protected:
    bool isTeacher;
    std::string mail;
    unsigned long phone;
    static void checkPhone(unsigned long &phone);
    static bool isMailCharacter(char & c);
    static void checkMail(std::string &mail );
public:
    static bool isPhone(unsigned long &phone);
    static bool isMail(std::string&mail);
    std::string getMail();
    std::string getPhone();
    bool getIsTeacher();
    bool operator!=(Person &person);
    bool operator==(Person &person);
};

#endif //PROJECT_TWO_PERSON_HPP
