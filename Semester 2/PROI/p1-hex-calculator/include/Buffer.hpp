//
// Created by Wojtek on 12/03/2018.
//

#ifndef PROJEKT_JEDEN_BUFFER_HPP
#define PROJEKT_JEDEN_BUFFER_HPP
#include <iostream>
#include <sstream>
#include "Calculator.hpp"
#include "Op.hpp"

class Buffer{
    bool continuationFlag;
    std::stringstream stream;



    static  bool isOperat(Op p);
    static  bool isParenthesis(Op p);

    static  int priority(Op p);

public:

    Buffer();

    void askForExpression();

    bool extractExpression(Calculator &calc);

     bool getContFlag();

};
#endif //PROJEKT_JEDEN_BUFFER_HPP
