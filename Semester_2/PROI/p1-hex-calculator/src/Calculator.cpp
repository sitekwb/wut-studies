#include <iostream>
#include "Calculator.hpp"

using namespace std;

     bool Calculator::isOperat(Op p){
        return p!=empty;
    }
     Calculator::Calculator(){
        errorFlag=false;
    }
     bool Calculator::getErrorFlag(){ return errorFlag; }


     	bool Calculator::pushOperatStack(Op p){
        if(!isOperat(p)) return true;
        operat.push(p);
        return false;
    }
     Op Calculator::checkOut(){
        return out.front();
    }




bool Calculator::count(){
    int n = results.top();
    results.pop();
    int m = results.top();
    results.pop();
    Op p=out.front();
    out.pop();
    if(p==plusik) n+=m;
    else if(p==minusik) n=m-n;
    else if(p==multiply) n*=m;
    else if(p==divide){
        if(n==0) return true;
        n=m/n;
    }
    else return true;//if operator is unknown
    results.push(n);
    return false;
}

void Calculator::pushOut(int num){
	Op *p = new Op(num);
	out.push(*p);
    delete p;
}
bool Calculator::pushOut(Op p){
    if(p==empty) return true;
    out.push(p);
    return false;
}

	Op Calculator::checkOperatStack(){
		if(operat.empty()) return Op();
		return operat.top();
	}
	Op Calculator::getOperatStack(){
		Op p=this->checkOperatStack();
		if(p!=empty)operat.pop();
		return p;
	}
	int Calculator::getResult(){
		while(!out.empty()){
			if(out.front()==number){
				results.push(out.front().getNum());
                out.pop();
			}
			else if(this->count()) {errorFlag=true; return 0;}
            //cout<<hex<<results.top();//TEST
		}
		int y;
        //true if empty expression written
		if(!results.empty()) {
            y = results.top();
            results.pop();
        }
        else y=0;
		return y;
	}
	Calculator::~Calculator(){
		while(!out.empty()){
			out.pop();
		}
		while(!operat.empty()){
			operat.pop();
		}
		while(!results.empty()){
			results.pop();
		}
	}
