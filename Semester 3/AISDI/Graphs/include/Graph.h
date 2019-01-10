#ifndef AISDI_MAPS_HASHMAP_H
#define AISDI_MAPS_HASHMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <list>
#include <vector>
#include <iostream>
#include <random>

#include "Line.h"


namespace aisdi
{





class Graph {

public:
    using value_type = Node;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    class ConstIterator;
    class Iterator;

    using iterator = Iterator;
    using const_iterator = ConstIterator;


    ~Graph();

    Graph() {}

    Graph(size_t randomGraphSize){
      std::random_device rd;

      for(size_t i = 0; i < randomGraphSize; ++i){
          for(size_t j = i; j < randomGraphSize; ++j){
              if( rd() % 2 ){
                  add(i, j);
              }
          }
      }
    }

    bool isEmpty() const
    {
      return nodes.empty();
    }

    size_type getSize() const
    {
      return nodes.size();
    }

    void add(size_type first, size_type second);


    value_type *findNode(size_type number){
        for(auto node: nodes){
            if(node->number == number){
                return node;
            }
        }
        return nullptr;
    }

    void printGreatBridges(std::ostream& str = std::cout) const;

    bool isConnected(int,int) const;

    iterator begin();

    iterator end();

    const_iterator cbegin() const;

    const_iterator cend() const;

    const_iterator begin() const;

    const_iterator end() const;

    bool operator==(const Graph& other){
        return nodes==other.nodes && lines == other.lines;
    }
    bool operator!=(const Graph& other){
        return !operator==(other);
    }
    bool lineInUse(Line *line) const;
private:
    size_t getMaxNumber() const;
    void doDFS(const Node &node, size_t &visitedCount, bool *visited) const;

    std::list<Node *> nodes;
    std::list<Line *> lines;
    const static int NOTHING = -1;

};

class Graph::ConstIterator
{
public:
    using reference = typename Graph::const_reference;
    using value_type = typename Graph::value_type;
    using pointer = const typename Graph::value_type*;
    using list_iterator = typename std::list<value_type  *>::const_iterator;



    friend class Graph;

    explicit ConstIterator();

    explicit ConstIterator(Graph const *graph_, list_iterator element_) : graph(graph_), element(element_)
    {}

    ConstIterator(const ConstIterator& other)
    {
        graph = other.graph;
        element = other.element;
    }

    ConstIterator& operator++(){
        if(*this == graph->end()){
            throw std::out_of_range("Incrementing end()");
        }
        ++element;
        return *this;
    }

    ConstIterator operator++(int){
        auto tmp = *this;
        operator++();
        return tmp;
    }

    ConstIterator& operator--()
    {
        if(*this == graph->begin()){
            throw std::out_of_range("Cannot decrement begin");
        }
        --element;
        return *this;
    }

    ConstIterator operator--(int)
    {
        auto tmp = *this;
        operator--();
        return tmp;
    }

    reference operator*() const
    {
        if(*this == graph->end()){
            throw std::out_of_range("No value at end()");
        }
        return **element;
    }

    pointer operator->() const
    {
        return &this->operator*();
    }

    bool operator==(const ConstIterator& other) const
    {
        return ( element == other.element );
    }

    bool operator!=(const ConstIterator& other) const
    {
        return !(*this == other);
    }
protected:
    Graph const *graph;
    list_iterator element;
};

class Graph::Iterator : public Graph::ConstIterator
{
public:
    using reference = typename Graph::reference;
    using pointer = typename Graph::value_type*;

    explicit Iterator()
    {}

    Iterator(const ConstIterator& other)
            : ConstIterator(other)
    {}

    Iterator& operator++()
    {
        ConstIterator::operator++();
        return *this;
    }

    Iterator operator++(int)
    {
        auto result = *this;
        ConstIterator::operator++();
        return result;
    }

    Iterator& operator--()
    {
        ConstIterator::operator--();
        return *this;
    }

    Iterator operator--(int)
    {
        auto result = *this;
        ConstIterator::operator--();
        return result;
    }

    pointer operator->() const
    {
        return &this->operator*();
    }

    reference operator*() const
    {
        // ugly cast, yet reduces code duplication.
        return const_cast<reference>(ConstIterator::operator*());
    }
};

//again
/*
class Graph::ConstIterator {
public:
  using reference = typename Graph::const_reference;
  using value_type = typename Graph::value_type;
  using pointer = const typename Graph::value_type*;
  using list_iterator = typename std::list<value_type  *>::const_iterator;

  friend class Graph;

  ConstIterator(){}

  explicit ConstIterator(Graph const *graph_, list_iterator element_) : graph(graph_), element(element_)
  {}

  ConstIterator(const ConstIterator& other)
  {
    graph = other.graph;
    element = other.element;
  }

  ConstIterator& operator++(){
    if(*this == graph->end()){
        throw std::out_of_range("Incrementing end()");
    }
    ++element;
    return *this;
  }

    ConstIterator operator++(int){
        auto tmp = *this;
        operator++();
        return tmp;
    }

  ConstIterator& operator--()
  {
    if(*this == graph->begin()){
        throw std::out_of_range("Cannot decrement begin");
    }
    --element;
    return *this;
  }

  ConstIterator operator--(int)
  {
    auto tmp = *this;
    operator--();
    return tmp;
  }

  reference operator*() const
  {
      if(*this == graph->end()){
          throw std::out_of_range("No value at end()");
      }
      return **element;
  }

  pointer operator->() const
  {
    return &this->operator*();
  }

  bool operator==(const ConstIterator& other) const
  {
    return ( element == other.element );
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !(*this == other);
  }
protected:
    Graph const *graph;
    list_iterator element;
};

class Graph::Iterator : public Graph::ConstIterator
{
public:
  using reference = typename Graph::reference;
  using pointer = typename Graph::value_type*;

  explicit Iterator(){}

  Iterator(const ConstIterator& other)
    : ConstIterator(other)
  {}

  Iterator& operator++()
  {
    ConstIterator::operator++();
    return *this;
  }

  Iterator operator++(int)
  {
    auto result = *this;
    ConstIterator::operator++();
    return result;
  }

  Iterator& operator--()
  {
    ConstIterator::operator--();
    return *this;
  }

  Iterator operator--(int)
  {
    auto result = *this;
    ConstIterator::operator--();
    return result;
  }

  pointer operator->() const
  {
    return &this->operator*();
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};
*/
}

#endif /* AISDI_MAPS_HASHMAP_H */
