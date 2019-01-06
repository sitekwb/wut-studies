//
// Created by Wojciech Sitek on 04/01/2019.
//

#include "Graph.h"

using namespace aisdi;

Graph::~Graph() {
    if(!isCopy) {
        for (auto node: nodes) {
            delete node;
        }
        for (auto line: lines) {
            delete line;
        }
    }
}


Graph& Graph::operator=(const Graph& other)
{
    if(!isCopy){
        throw std::runtime_error("Not an only-pointer graph");
    }
    if(*this == other){
        return *this;
    }
    //remove all
    this->Graph::~Graph();

    //copy node and line pointers
    for(auto line: other.lines){
        lines.push_back(line);
    }
    for(auto node: other.nodes){
        nodes.push_back(node);
    }
    return *this;
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

void Graph::lightRemove(Node *node){
    if(!isCopy){
        throw std::runtime_error("Not an only-pointer graph");
    }
    //delete only pointers
    nodes.remove(node);
    for(auto it = lines.begin(); it != lines.end(); ++it){
        if((*it)->isPresent(node)){
            lines.erase(it);
        }
    }
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
bool Graph::isConnected() const{
    if(isEmpty()){
        return true; //empty graph is connected
    }

    const Node &node = *begin();
    size_type visitedCount = 0;

    auto size = getMaxNumber() + 1;
    bool visited[size];
    for(size_t i = 0; i < size; ++i){
        visited[i] = false;
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
        Graph graph(*this); //this constructor copies only pointers
        graph.lightRemove(line->first);
        graph.lightRemove(line->second);
        if(!graph.isConnected()){
            str<<line->first->number<<' '<<line->second->number<<std::endl;
        }
    }
}
