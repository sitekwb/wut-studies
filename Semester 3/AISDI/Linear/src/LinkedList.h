#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iterator>

namespace aisdi
{

template <typename Type>
struct Element{
  Type value;
  Element *next;
  Element *prev;

  Element(){}

  Element(const Type &item){
    value = item;
  }
};

template <typename Type>
class LinkedList
{
public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using value_type = Type;
  using pointer = Type*;
  using reference = Type&;
  using const_pointer = const Type*;
  using const_reference = const Type&;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;


  LinkedList()
  {
    init();
  }

  LinkedList(std::initializer_list<Type> l)
  {
    init();
    for(auto elementIt = l.begin(); elementIt != l.end(); ++elementIt){
      this->append(*elementIt);
    }
  }

  LinkedList(const LinkedList& other)
  {
      init();
      for(auto it = other.begin(); it != other.end(); it++){
          this->append(*it);
      }
  }

  LinkedList(LinkedList&& other)
  {
    init();
    //swap lists
    *this = std::move(other);
  }


  ~LinkedList()
  {
    removeList();
    delete sentinel;
    count = 0;
  }

  LinkedList& operator=(const LinkedList& other)
  {
    if(other.sentinel != this->sentinel){
      removeList();
      for(auto it = other.begin(); it != other.end(); it++){
        this->append(*it);
      }
    }
    return *this;
  }



  LinkedList& operator=(LinkedList&& other)
  {
    if(this->sentinel != other.sentinel) {
      auto tmp = sentinel;
      sentinel = other.sentinel;
      other.sentinel = tmp;

      auto tmp2 = count;
      count = other.count;
      other.count = tmp2;

      other.removeList();
    }
    return *this;
  }

  bool isEmpty() const
  {
    return count==0;
  }

  size_type getSize() const
  {
    return count;
  }

  void append(const Type item)
  {
    Element<Type> *newElement = new Element<Type>(item);

    auto last = sentinel->prev;
    last->next = newElement;
    newElement->prev = last;
    newElement->next = sentinel;
    sentinel->prev = newElement;
    ++count;
  }

  void prepend(const Type& item)
  {
    auto *newElement = new Element<Type>(item);

    auto first = sentinel->next;
    first->prev = newElement;
    newElement->next = first;
    newElement->prev = sentinel;
    sentinel->next = newElement;
    ++count;
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
    auto after = insertPosition.it;
    auto before = after->prev;

    auto *newElement = new Element<Type>(item);

    before->next = newElement;
    newElement->prev = before;
    newElement->next = after;
    after->prev = newElement;
    count += 1;
  }

  Type popFirst()
  {
    if(this->isEmpty()){
        throw std::logic_error("Empty collection");
    }
    //declaration of temporary variables
    auto first = sentinel->next;
    auto second = first->next;
    // removing first from neibourgh pointers
    sentinel->next = second;
    second->prev = sentinel;
    // remember value to return
    value_type value = first->value;
    // delete first
    --count;
    delete first;

    return value;
  }

  const Type &operator[](size_t n){
      if(n>=count){
          throw std::out_of_range("");
      }
      auto it = (n<count/2) ? (begin()+n) : ( end()-(count-n) );
      return *it;
  }

  Type popLast()
  {
      if(this->isEmpty()){
          throw std::logic_error("Empty collection");
      }
      //declaration of temporary variables
      auto last = sentinel->prev;
      auto second = last->prev;
      // removing first from neibourgh pointers
      sentinel->prev = second;
      second->next = sentinel;
      // remember value to return
      value_type value = last->value;
      // delete last
      --count;
      delete last;

      return value;
  }

  void erase(const const_iterator& position)
  {
      if(this->isEmpty()){
          throw std::out_of_range("Collection empty");
      }
      //find element
      auto element = position.it;

      if(element == sentinel){
        throw std::out_of_range("Iterator out of range");
      }
      //declaration of temporary variables
      auto before = element->prev;
      auto after = element->next;
      // removing element from neibourgh pointers
      before->next = after;
      after->prev = before;
      // delete element
      --count;
      delete element;
  }
  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {
    if(firstIncluded.sentinel != this->sentinel || lastExcluded.sentinel != this->sentinel){
      throw std::runtime_error("Not this list");
    }
    for(auto it = firstIncluded; it != lastExcluded; ++it){
      if(it == this->end()){
        throw std::runtime_error("First after last.");
      }
      erase(it);
    }
  }

  iterator begin()
  {
    return iterator(sentinel->next, sentinel);
  }

  iterator end()
  {
    return iterator(sentinel, sentinel);
  }

  const_iterator cbegin() const
  {
    return const_iterator(sentinel->next, sentinel);
  }

  const_iterator cend() const
  {
    return const_iterator(sentinel, sentinel);
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
  void removeList(){
    if(!this->isEmpty()){
      erase( this->begin(), this->end() );
    }
  }
  void init(){
      sentinel = new Element<value_type>();

      sentinel->prev = sentinel;
      sentinel->next = sentinel;
      count = 0;
  }
  Element<Type> *sentinel;
  std::size_t count;
};

template <typename Type>
class LinkedList<Type>::ConstIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename LinkedList::value_type;
  using difference_type = typename LinkedList::difference_type;
  using pointer = typename LinkedList::const_pointer;
  using reference = typename LinkedList::const_reference;

  friend class LinkedList<value_type>;

  explicit ConstIterator()
  {}

  ConstIterator(Element<value_type> *element, Element<value_type> *sentinel){
    this->it = element;
    this->sentinel = sentinel;
  }


  reference operator*() const
  {
    if(it == sentinel){
      throw std::out_of_range("End of collection");
    }
    return it->value;
  }

  ConstIterator& operator++()
  {
    if(it == sentinel){
      throw std::out_of_range("End of collection incremented");
    }
    it = it->next;
    return *this;
  }

  ConstIterator operator++(int)
  {
    if(it == sentinel){
      throw std::out_of_range("End of collection incremented");
    }
    it = it->next;
    return const_iterator(it->prev, sentinel);
  }

  ConstIterator& operator--()
  {
    it = it->prev;
    if(it == sentinel){
      throw std::out_of_range("Begin of collection decremented");
    }
    return *this;
  }

  ConstIterator operator--(int)
  {
    it = it->prev;
    if(it == sentinel){
      throw std::out_of_range("Begin of collection decremented");
    }
    return const_iterator(it->next, sentinel);
  }

  ConstIterator operator+(difference_type d) const
  {
    Element<value_type> *element = it;
    for(difference_type i=0; i<d; ++i){
      if(element == sentinel){
        throw std::out_of_range("Out of range");
      }
      element = element->next;
    }
    ConstIterator it(element, sentinel);
    return it;
  }

  ConstIterator operator-(difference_type d) const
  {
    Element<value_type> *element = it;
    for(difference_type i=0; i<d; ++i){
      element = element->prev;
      if(element == sentinel){
        throw std::out_of_range("Out of range");
      }

    }
    ConstIterator it(element, sentinel);
    return it;
  }


  bool operator==(const ConstIterator& other) const
  {
    return ( this->it == other.it && this->sentinel == other.sentinel );
  }

  bool operator!=(const ConstIterator& other) const
  {
    return ! (*this == other);
  }

protected:
  Element<value_type> *it, *sentinel;
};

template <typename Type>
class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
{
public:
  using pointer = typename LinkedList::pointer;
  using reference = typename LinkedList::reference;

  explicit Iterator()
  {}

  Iterator(Element<value_type> *element, Element<value_type> *sentinel){
    this->it = element;
    this->sentinel = sentinel;
  }
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

  Iterator operator+(difference_type d) const
  {
    return ConstIterator::operator+(d);
  }

  Iterator operator-(difference_type d) const
  {
    return ConstIterator::operator-(d);
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif // AISDI_LINEAR_LINKEDLIST_H
