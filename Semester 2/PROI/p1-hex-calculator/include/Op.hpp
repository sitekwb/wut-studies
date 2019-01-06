//
// Created by Wojtek on 13/03/2018.
//

#ifndef PROJEKT_JEDEN_OPERATOR_HPP
#define PROJEKT_JEDEN_OPERATOR_HPP

#include <iostream>
#include <sstream>

enum op_t{empty, number, plusik, minusik, multiply, divide, openingPar, closingPar};
const char opArray[] = {0,'L','+','-','*','/', '(', ')'};
class Op{
    op_t op;
    int num;
public:
    static  bool isHexDigit(char c);

    Op();
    Op(op_t a);
    Op(int n);

    op_t get();
    char getChar();
    void setOp( op_t a);
    void setOp( int n);
    void setOp ( Op a);
    int getNum();
    void setNum( int n);
    bool setVal(char c);;
    bool operator==(op_t value);
    bool operator!=(op_t value);
    void operator=(op_t value);

    void operator=(Op value);

    bool operator==(int value);
    bool operator!=(int value);
    void operator=(int value);
	friend bool operator>>(std::stringstream& is, Op& p);

};


#endif //PROJEKT_JEDEN_OPERATOR_HPP
