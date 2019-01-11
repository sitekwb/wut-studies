//
// Created by Wojtek on 12/03/2018.
//

#ifndef PROJEKT_JEDEN_CALCULATOR_HPP
#define PROJEKT_JEDEN_CALCULATOR_HPP
#include <iostream>
#include <stack>
#include <queue>
#include "Op.hpp"

class Calculator{
    std::queue<Op> out;
    std::stack<Op> operat;
    std::stack<int> results;
    bool errorFlag;

     bool isOperat(Op p);
    bool count();
public:
     Calculator();
     bool getErrorFlag();


    void pushOut(int num);
    bool pushOut(Op p);
     	bool pushOperatStack(Op p);
     Op checkOut();
    Op checkOperatStack();
    Op getOperatStack();
    int getResult();
    ~Calculator();
};
#endif //PROJEKT_JEDEN_CALCULATOR_HPP
