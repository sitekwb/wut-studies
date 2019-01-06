//
// Created by Wojciech Sitek on 14/12/2018.
//

#include "Letter.hpp"


char Letter::operator++(){

    c = (c=='z')?'a':( (c=='Z')?'A':(c+1) );
    return c;
}
char Letter::operator++(int){
    char tmp = c;
    operator++();
    return tmp;
}
char Letter::operator*(){
    return c;
}