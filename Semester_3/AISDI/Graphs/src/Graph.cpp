//
// Created by Wojciech Sitek on 04/01/2019.
//

#include "Graph.h"

using namespace aisdi;

Graph::~Graph() {
    for (auto node: nodes) {
        delete node;
    }
    for (auto line: lines) {
        delete line;
    }
}


void Graph::add(size_type first, size_type second){
    auto node1 = findNode(first);
    auto node2 = findNode(second);
    if(!node1){
        node1 = new Node(first);
        nodes.push_back(node1);
    }
    if(!node2){
        node2 = new Node(second);
        nodes.push_back(node2);
    }
    auto line = new Line(node1, node2);
    lines.push_back(line);
    node1->lines.push_back(line);
    node2->lines.push_back(line);
}

Graph::iterator Graph::begin()
{
    return Iterator(cbegin());
}

Graph::iterator Graph::end()
{
    return Iterator(cend());
}

Graph::const_iterator Graph::cbegin() const
{
    return ConstIterator(this, nodes.begin());
}

Graph::const_iterator Graph::cend() const
{
    return ConstIterator(this, nodes.end());
}

Graph::const_iterator Graph::begin() const
{
    return cbegin();
}

Graph::const_iterator Graph::end() const
{
    return cend();
}

size_t Graph::getMaxNumber() const{
    size_t max = 0;
    for(auto node: nodes){
        if( node->number > max ){
            max = node->number;
        }
    }
    return max;
}
bool Graph::isConnected(int exclude1 = NOTHING, int exclude2 = NOTHING) const{
    if(isEmpty()){
        return true; //empty graph is connected
    }

    //find not excluded node
    auto node_it = begin();
    for( ; node_it != end(); ++node_it){
        if(exclude1 != node_it->number && exclude2 != node_it->number){
            break;
        }
    }
    if(node_it == end()){
        return true; //graph built of only 2 excluded nodes => connected
    }
    const Node &node = *node_it;


    size_type visitedCount = 0;

    auto size = getMaxNumber() + 1;
    bool visited[size];
    for(size_t i = 0; i < size; ++i){
        visited[i] = false;
    }
    if(exclude1 != NOTHING && exclude2 != NOTHING){
        visited[exclude1] = true;
        visited[exclude2] = true;
        visitedCount += 2;
    }
    doDFS(node, visitedCount, visited);

    return visitedCount == getSize();
}

void Graph::doDFS(const Node &node, size_t &visitedCount, bool *visited) const{
    visited[node.number] = true;
    ++visitedCount;
    for(auto line: node.lines){
        if(!lineInUse(line)){
            continue;
        }
        auto &friendNode = line->getFriend(node);
        if(!visited[friendNode.number]) {
            doDFS(friendNode, visitedCount, visited);
        }
    }
}

bool Graph::lineInUse(Line *line_) const{
    for(auto line: lines){
        if(line == line_){
            return true;
        }
    }
    return false;
}

void Graph::printGreatBridges(std::ostream &str) const{
    for(auto line: lines){
        if(!this->isConnected(line->first->number, line->second->number)){
            str<<line->first->number<<' '<<line->second->number<<std::endl;
        }
    }
}
