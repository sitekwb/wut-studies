//
// Created by Wojtek on 13/03/2018.
//
#include <iostream>
#include "Op.hpp"
using namespace std;



	bool Op::isHexDigit(char c){
        return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
    }

     Op::Op(){ op=empty;}
     Op::Op(op_t a){ if(a!=number) op=a;    else op=empty; }
     Op::Op(int n){ op=number; num=n; }

     op_t Op::get(){ return op; }
     char Op::getChar(){ return opArray[op]; }
     void Op::setOp( op_t a){ if(a!=number)op=a; else op=empty;}
     void Op::setOp( int n){ op=number; num=n; }
     void Op::setOp ( Op a){
        if(a.get()==number) setOp(a.getNum());
        else setOp(a.get());
    }
     int Op::getNum(){
        if(op==number) return num;
        else return 0;
    }
     void Op::setNum( int n){ num=n;}
     bool Op::setVal(char c){
        bool flag=true;
        for (int i=0;i<9;++i){
            if(c==opArray[i]){
                op=static_cast<op_t>(i);//save char in the operator
                flag=false;
                break;
            }
        }

        return flag;//if flag is true, there wasn't good char for this type

    }
     bool Op::operator==(op_t value){ return this->get()==value; }
     bool Op::operator!=(op_t value){ return this->get()!=value; }
     void Op::operator=(op_t value){ setOp(value); }//niezmiennik: if op=number, num must be defined

     void Op::operator=(Op value){ setOp(value); }

     bool Op::operator==(int value){ return this->getNum()==value; }
     bool Op::operator!=(int value){ return this->getNum()!=value; }
     void Op::operator=(int value){ op=number; num=value; }//niezmiennik: if op=number, num must be defined













bool operator>>(std::stringstream& is, Op& p){

    char c;
    is >> c;
    if(p.isHexDigit(c)){
        is.unget();
        int num;
        is >> std::hex >> num;
        p=num;
        return false;
    }

    return p.setVal(c); //returns true if error in setting value
}
