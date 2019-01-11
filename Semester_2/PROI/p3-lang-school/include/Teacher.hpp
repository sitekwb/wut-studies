//
// Created by wojtek on 22.05.18.
//

#ifndef PROJECT_TWO_TEACHER_HPP
#define PROJECT_TWO_TEACHER_HPP

#include <string>
#include <vector>
#include "Worker.hpp"
#include "InputException.hpp"

class Teacher: public Worker{
    std::string language;
    std::vector<int>groups;
public:
    Teacher(int teachId, std::string teachName, int teachSalary, std::string lang);
    void print();
    void addGroup(int group);
    std::string getLang();
    void setLang(std::string lang);
};

#endif //PROJECT_TWO_TEACHER_HPP
