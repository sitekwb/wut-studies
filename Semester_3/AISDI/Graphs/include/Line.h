//
// Created by Wojciech Sitek on 04/01/2019.
//

#ifndef AISDI_GRAPHS_LINE_H
#define AISDI_GRAPHS_LINE_H

#include "Node.h"


class Line{

public:
    Node *first, *second;
    Line(Node *first_, Node *second_) : first(first_), second(second_) {}

    const Node &getFriend(const Node &node) const{
        return (&node == first) ? *second : *first;
    }

    bool isPresent(Node *node){
        return first == node || second == node;
    }
};




#endif //AISDI_GRAPHS_LINE_H
