#include <iostream>
#include "Buffer.hpp"
using namespace std;


    bool Buffer::isOperat(Op p){
        return p != number && p != empty;
    }
    bool Buffer::isParenthesis(Op p){
        return (p == openingPar || p == closingPar);
    }

    int Buffer::priority(Op p){
        if(p==empty) return -1;
        if(p==openingPar) return 0;
        if(p==plusik||p==minusik||p==closingPar) return 1;
        return 3;
    }

    Buffer::Buffer(){
        continuationFlag=true;
    }

    
     bool Buffer::getContFlag(){ return continuationFlag; }


	
void Buffer::askForExpression(){
    cout<<"Type q to finish program."<<endl<<"Enter hexadecimal algebraic expression: ";
    string chain;
    getline(cin, chain);
    if(!cin.good()) { cin.clear(); cin.ignore(1000, '\n'); }
    if(chain.compare("q")==0) continuationFlag=false;
    stream<<chain;
}
	
bool Buffer::extractExpression(Calculator &calc) {
    Op beforeOp;
    beforeOp=openingPar;//the most universal ( sign is first beforeOp, because everything can be after it
    bool okFlag = true;//it is false, if there is an error, breaks the calculation
    bool unarMinusFlag = false;
    while (stream.good() && okFlag) { //okFlag if false, breaks the process
        Op p;
        if(stream>>p) {okFlag=false; break;}//function sets p value
                                        // and returns true if there is illegal sign

        if (p == minusik && beforeOp == openingPar) {
            unarMinusFlag = true;
            beforeOp=p;
            continue;
        }
        if (p==number) {
            if (!isOperat(beforeOp)) okFlag = false; //if there isn't operator before number => error
            calc.pushOut(((unarMinusFlag) ? (-1) : 1) * p.getNum()); //push number to out queue
            //cout<<"OUT:"<<calc.checkOut().getNum()<<endl;//TEST
            //cout<<((unarMinusFlag) ? (-1) : 1) * p.getNum()<<endl;//TEST
            unarMinusFlag = false;
        }
        else{//if is not a number, then it is an operator
            //cout<<"INPUT:"<<p.getChar()<<endl;//TEST
            if (!isParenthesis(p) && isOperat(beforeOp) && beforeOp != closingPar)
                okFlag = false;
            //there shouldn't be operators +-*/ after operators (+-*/
            if (p == openingPar) calc.pushOperatStack(p);
            else if (p == closingPar) {
                while (calc.checkOperatStack() != openingPar) {//while I won't find left parenthesis
                    if (calc.checkOperatStack() == empty) {//if I didn't find it and finished stack => error
                        okFlag = false;
                        break;
                    }
                    calc.pushOut(calc.getOperatStack());//take operators to queue, according to algorithm
                    //cout<<"OUTOPERAT:"<<calc.checkOut().getChar()<<endl;//TEST
                }
                calc.getOperatStack(); //delete ( from stack

                //problem of last ) at the end
                char d;
                stream>>d;
                if(stream.good()) stream.unget();
                else break;

            }
            else { //if not (), then it must be */+-
                while (priority(p) <= priority(calc.checkOperatStack())) {//while on stack is more prioritased op
                    calc.pushOut(calc.getOperatStack());//take it out to queue
                }
                calc.pushOperatStack(p);
            }
        }
        beforeOp=p; //inform next loop about operator or number that was read

    }
    //if nothing more to read from stream
    if (stream.eof()) {//end of reading
        //take every operand from stack to out
        while (calc.checkOperatStack() != empty) {
            //if there are ( signs, there were wrong parenthesis entered
            if (calc.checkOperatStack() == openingPar) {
                okFlag = false;
                break;
            }
            //take everything to out
            calc.pushOut(calc.getOperatStack());
        }
    }
    stream.str(string());//clear stream for next expressions
    stream.clear();//               ---||---
    return !okFlag;//false for good input and true for error
}
