//
// Created by Wojciech Sitek on 12/11/2018.
//
#include "Buffer.hpp"

using namespace std;

bool Buffer::isEmpty(){
    return tabsize == 0;
}

bool Buffer::isFull(){
    return tabsize == capacity;
}

char Buffer::pick() { //throws runtime_error
    char c;
    if(isEmpty()){
        throw std::runtime_error("Empty tab! Fatal error!");
    }
    c = this->front();
    this->pop();
    return c;
}
void Buffer::add(char element){ //throws runttime_error
    if(this->isFull()){
        throw runtime_error("Full queue");
    }
    this->push(element);
}
void Buffer::pop(){
    for(auto i = 1; i < tabsize; ++i){
        tab[i-1] = tab[i];
    }
    --tabsize;
}
void Buffer::push(char element){
    tab[tabsize++] = element;
}
int Buffer::getSize(){
    return tabsize;
}
char Buffer::front() {
    return tab[0];
}
string Buffer::getBuf(){
    string str;
    while( str.size() != tabsize ){
        char c;
        c = front();
        this->pop();
        this->push(c);
        str+=c;
    }
    return str;
}
int Buffer::getCapacity() const{
    return capacity;
}
char Buffer::getBack(){
    return tab[tabsize-1];
}
