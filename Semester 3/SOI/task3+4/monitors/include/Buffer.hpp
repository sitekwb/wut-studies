//
// Created by Wojciech Sitek on 12/11/2018.
//

#ifndef T3_BUFFER_HPP
#define T3_BUFFER_HPP

#include "Monitor.hpp"

#include <iostream>
#include <stdexcept>
#include <queue>

#define BUF_NUM_ELEMENTS        9



class Buffer{
public:
    Buffer(char *tab_, int &tabsize_) : tab(tab_), tabsize(tabsize_){}
    bool isEmpty();
    bool isFull();
    char pick();
    void add(char element);
    int getSize();
    std::string getBuf();
    int getCapacity() const;
    char getBack();
private:
    void push(char);
    void pop();
    char front();
    static const int capacity = BUF_NUM_ELEMENTS;
    char *tab;
    int &tabsize;
};

#endif //T3_BUFFER_HPP
