//
// Created by wojtek on 15.04.18.
//

#ifndef PROJECT_TWO_MENU_HPP
#define PROJECT_TWO_MENU_HPP


#include <iostream>
#include <string>
#include <vector>

class Menu{
protected:
    std::string title;
    std::string question;
    std::vector<std::string>options;
    std::string write;
    int actionNo;
public:
    Menu();
    Menu(std::string t, std::string q, std::vector<std::string>& opt, std::string w="Enter appropriate command number: ");
    Menu(std::string t, std::string q, std::string w="Enter appropriate command number: ");
    int show(std::string message="");
    int addOption(std::string opt, int position=-1/*starting from 0, -1 means end*/);

    int eraseOption(int position/*starting from 0*/);
    int eraseOption(int first, int last);

    ~Menu();
};

#endif //PROJECT_TWO_MENU_HPP
