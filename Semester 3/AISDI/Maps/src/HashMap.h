#ifndef AISDI_MAPS_HASHMAP_H
#define AISDI_MAPS_HASHMAP_H

#include "OperationCountingObject.h"

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <list>
#include <vector>


#define HASHMAPSIZE     100000



namespace aisdi
{

template <typename KeyType, typename ValueType>
class HashMap
{
public:
  using key_type = KeyType;
  using mapped_type = ValueType;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;


    friend class HashMap<KeyType,ValueType>::ConstIterator;

    ~HashMap()
    {
        if(list){
            for(auto it = list->begin(); it != list->end(); ++it){
                delete *it;
            }
            delete list;
        }
        if(tab){
            delete tab;
        }
        list = nullptr;
        tab = nullptr;
    }

    HashMap()
    {
        initAllocate();
        initTab();
    }

    HashMap(std::initializer_list<value_type> l)
    {
        initAllocate();
      initTab((l.size() > HASHMAPSIZE) ? (l.size()*2) : HASHMAPSIZE);
      for(auto it = l.begin(); it != l.end(); ++it){
          operator[](it->first) = it->second;
      }
    }

    HashMap(const HashMap& other)
    {
      initAllocate();
      *this = other;
    }

    HashMap(HashMap&& other)
    {
        tab = nullptr;
        list = nullptr;
        std::swap(tab, other.tab);
        std::swap(list, other.list);
    }

    HashMap& operator=(const HashMap& other)
    {
      if(*this == other){
          return *this;
      }
      //remove all
      for( auto it = begin(); it != end(); it = begin() ){
          remove(it);
      }

      //copy tab
      if(other.tab->size() > tab->size()) {
          initTab( other.tab->size() - tab->size() );
      }
      for(auto it = other.begin(); it != other.end(); ++it){
          operator[](it->first) = it->second;
      }
      return *this;
    }

    HashMap& operator=(HashMap&& other)
    {
      //destroy elements of this
      this->HashMap::~HashMap();
      std::swap(tab, other.tab);
      std::swap(list, other.list);
      return *this;
    }

    bool isEmpty() const
    {
      return list->size() == 0;
    }

    mapped_type& operator[](const key_type& key)
    {
      if(tab->operator[](hash(key)).empty()) {
          //create object
          auto v = new value_type(key, mapped_type());

          //insert to tab
          tab->operator[](hash(key)).push_back( v );

          //insert to list
          auto position = list->begin();
          while(position != list->end() && (*position)->first <= key){
              ++position;
          }
          list->insert(position, v);
      }
      return tab->operator[](hash(key)).back()->second;
    }

    const mapped_type& valueOf(const key_type& key) const
    {
        if(tab->operator[](hash(key)).empty()){
            throw std::out_of_range("Not found");
        }
        return tab->operator[](hash(key)).front()->second;
    }

    mapped_type& valueOf(const key_type& key)
    {
      if(tab->operator[](hash(key)).empty()){
          throw std::out_of_range("Not found");
      }
      return tab->operator[](hash(key)).front()->second;
    }

    const_iterator find(const key_type& key) const
    {
        if(tab->operator[](hash(key)).empty()){
            return cend();
        }
        auto it = list->begin();
        while((*it)->first != key){
            ++it;
        }
        return Iterator(ConstIterator(this, it));
    }

    iterator find(const key_type& key)
    {
      if(tab->operator[](hash(key)).empty()){
          return cend();
      }
      auto it = list->begin();
      while(it != list->end() && (*it)->first != key){
          ++it;
      }
      return Iterator(ConstIterator(this, it));
    }

    void remove(const key_type& key)
    {
        remove(find(key));
    }

    void remove(const const_iterator& it)
    {
        if(it == end()){
            throw std::out_of_range("Cannot delete");
        }
        //if not end then exists
        auto pair = it.operator->();
        list->erase(it.element);

        //erase from tab.list
        auto linked = tab->operator[](pair->first);
        for(auto lit = linked.begin(); lit != linked.end(); ++lit){
            if(*lit == pair){
                linked.erase(lit);
                break;
            }
        }
        delete pair;
    }

    size_type getSize() const
    {
      return list->size();
    }

    bool operator==(const HashMap& other) const
    {
      auto it2 = other.begin();
      for(auto it1 = begin(); it1!=end(); ++it1, ++it2){
          if(it2 == other.end() || *it1 != *it2){
              return false;
          }
      }
      return ( it2 == other.end() );
    }

    bool operator!=(const HashMap& other) const
    {
        return !(*this == other);
    }

    iterator begin()
    {
        return Iterator(cbegin());
    }

    iterator end()
    {
      return Iterator(cend());
    }

    const_iterator cbegin() const
    {
      return ConstIterator(this, list->begin());
    }

    const_iterator cend() const
    {
        return ConstIterator(this, list->end());
    }

    const_iterator begin() const
    {
        return cbegin();
    }

    const_iterator end() const
    {
        return cend();
    }
private:
    void initAllocate(){
        tab = new std::vector< std::list<value_type *> >;
        list = new std::list<value_type *>;
    }
    void initTab(size_type capacity = HASHMAPSIZE){
        std::list<value_type *> linkedList;
        tab->insert(tab->end(), capacity, linkedList);
    }
    size_type hash(const key_type &key) const{
        return std::hash<key_type>{}( const_cast<key_type&>(key) ) % tab->size();
    }

    
    std::vector< std::list<value_type *> > *tab;
    std::list<value_type *> *list;
};

template <typename KeyType, typename ValueType>
class HashMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename HashMap::const_reference;
  using value_type = typename HashMap::value_type;
  using pointer = const typename HashMap::value_type*;
  using list_iterator = typename std::list<value_type  *>::const_iterator;



  friend class HashMap<KeyType, ValueType>;

  explicit ConstIterator(HashMap<KeyType, ValueType> const *map_, list_iterator element_) : map(map_), element(element_)
  {}

  ConstIterator(const ConstIterator& other)
  {
    map = other.map;
    element = other.element;
  }

  ConstIterator& operator++(){
    if(*this == map->end()){
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
    if(*this == map->begin()){
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
      if(*this == map->end()){
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
    HashMap<KeyType, ValueType> const *map;
    list_iterator element;
};

template <typename KeyType, typename ValueType>
class HashMap<KeyType, ValueType>::Iterator : public HashMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename HashMap::reference;
  using pointer = typename HashMap::value_type*;

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

}

#endif /* AISDI_MAPS_HASHMAP_H */
