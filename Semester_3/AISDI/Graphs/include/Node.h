//
// Created by Wojciech Sitek on 04/01/2019.
//

#ifndef AISDI_GRAPHS_NODE_H
#define AISDI_GRAPHS_NODE_H

#include <list>
#include <iostream>

class Line;

class Node{
    friend class Line;
public:

    Node(size_t number_) : number(number_){}

    std::list<Line *> lines;
    size_t number;
};

#endif //AISDI_GRAPHS_NODE_H
