#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iterator>


#define INIT_SIZE     100
#define DUPLEX        0
namespace aisdi
{

template <typename Type>
class Vector
{
public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = Type*;
  using reference = Type&;
  using const_pointer = const Type*;
  using const_reference = const Type&;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;


    Vector()
  {
    init();
  }

  Vector(std::initializer_list<Type> l)
  {
    if(l.size() > INIT_SIZE) {
      max = l.size() * 2;
    }
    else{
      max = INIT_SIZE;
    }
    tab = new Type[max];
    //insert values
    count = 0;
    for(auto it = l.begin(); it != l.end();){
      tab[count++] = *(it++);
    }
  }

  Vector(const Vector& other)
  {
    //allocate and copy
    if(other.getSize() > INIT_SIZE) {
      max = 2 * other.getSize();
    }
    else{
      max = INIT_SIZE;
    }
    tab = new Type[max];
    count = 0;
    for(auto it = other.begin(); it!=other.end();){
      tab[count++] = *(it++);
    }
  }

  Vector(Vector&& other)
  {
      tab = other.tab;
      count = other.count;
      max = other.max;

      other.tab = nullptr;
      other.max = 0;
      other.count=0;
  }

  ~Vector()
  {
    delete[] tab;
  }
  const Type &operator[](size_t n){
    if(n>count){
        throw std::out_of_range("");
    }
    return tab[n];
  }

  Vector& operator=(const Vector& other)
  {
    if(other.tab != this->tab){
      //copy other to tab
      if(other.count > max){
        allocate(other.count);
      }
      count = 0;
      for(auto it = other.begin(); it != other.end(); it++){
        this->append(*it);
      }
    }
    return *this;
  }

  Vector& operator=(Vector&& other)
  {
    if(this->tab != other.tab) {
      delete []tab;
      tab = nullptr;
      count = 0;
      max = 0;
      std::swap(tab, other.tab);
      std::swap(count, other.count);
      std::swap(max, other.max);
    }
    return *this;
  }

  bool isEmpty() const
  {
    return count == 0;
  }

  size_type getSize() const
  {
    return count;
  }

  void append(const Type& item)
  {
    if(count == max ){
      allocate();
    }
    tab[count++] = item;
  }

  void prepend(const Type& item)
  {
    if(count == max ){
      allocate();
    }
    for(size_type i = count; i>0; --i){
      tab[i] = tab[i-1];
    }
    tab[0] = item;
    ++count;
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
    if( count == max ){
      allocate();
    }
    if(insertPosition == end()) {
        tab[count++] = item;
        return;
    }
    size_t index = count;
    auto it = end()-1;
    for(; it != insertPosition; --it, --index){
        tab[index] = *it;
    }
    tab[index] = *it;//tab[insertPosition+1]
    tab[--index] = item;//tab[insertPosition]
    ++count;
  }

  Type popFirst()
  {
    if(this->isEmpty()){
      throw std::out_of_range("");
    }
    auto tmp = tab[0];
    --count;
    for(size_type i = 0; i<count; ++i){
      tab[i] = tab[i+1];
    }
    return tmp;
  }

  Type popLast()
  {
    if(this->isEmpty()){
      throw std::out_of_range("");
    }
    return tab[--count];
  }

  void erase(const const_iterator& position)
  {
    if(position == this->end()){
      throw std::out_of_range("");
    }
      size_t index = position.index;
      for(auto it = position+1; it != end(); ++it, ++index){
          tab[index] = *it;
      }
      --count;
  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {
    difference_type d = lastExcluded.index - firstIncluded.index;
    auto it = lastExcluded;
    for(size_t index = firstIncluded.index; it != end(); ++it, ++index){
      tab[index] = *it;
    }
    count-=d;
  }

  iterator begin()
  {
    return iterator(cbegin());
  }

  iterator end()
  {
    return iterator(cend());
  }

  const_iterator cbegin() const
  {
    return const_iterator(this, 0);
  }

  const_iterator cend() const
  {
    return const_iterator(this, count);
  }

  const_iterator begin() const
  {
    return cbegin();
  }

  const_iterator end() const
  {
    return cend();
  }

  friend class Vector<Type>::ConstIterator;

private:
  void allocate(size_type size=DUPLEX){
    if(size == DUPLEX){
      size = max;
    }
    Type *tmp = new Type[size*2];
    size_type i = 0;
    for(auto it = this->begin(); it!=this->end();){
      tmp[i++] = *(it++);
    }
    delete[] tab;
    tab = tmp;
    max=2*size;
  }

  void init(){
    tab = new Type[INIT_SIZE];
    max = INIT_SIZE;
    count = 0;
  }

  Type *tab;
  size_t count, max;
};

template <typename Type>
class Vector<Type>::ConstIterator
{

protected:
  const size_t index;
  Vector<Type> const *vector;
public:

  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = typename Vector::difference_type;
  using pointer = typename Vector::const_pointer;
  using reference = typename Vector::const_reference;


  explicit ConstIterator(Vector<Type> const * vector_, const int index_) : index(index_), vector(vector_){}

  friend class Vector<Type>;

  reference operator*() const
  {
    if(*this == vector->end()){
      throw std::out_of_range("");
    }
    return vector->tab[index];
  }

  ConstIterator& operator++()
  {
    if(*this == vector->end()){
      throw std::out_of_range("Max index achieved.");
    }
    auto &indexRef = const_cast<size_t &>(index);
    ++indexRef;
    return *this;
  }

  ConstIterator operator++(int)
  {
    auto it = *this;
    operator++();
    return it;
  }

  ConstIterator& operator--()
  {
    if(*this == vector->begin()){
      throw std::out_of_range("Min index achieved.");
    }
    auto &indexRef = const_cast<size_t &>(index);
    --indexRef;
    return *this;
  }

  ConstIterator operator--(int)
  {
    auto it = *this;
    operator--();
    return it;
  }

  ConstIterator operator+(difference_type d) const
  {
    size_t &indexRef = const_cast<size_t &>(index);
    indexRef += d;
    if(indexRef > vector->count){
      indexRef = vector->count;
    }
    return *this;
  }

  ConstIterator operator-(difference_type d) const
  {
    auto &indexRef = const_cast<size_t &>(index);
    indexRef -= d;
    if(indexRef < 0){
      indexRef = 0;
    }
    return *this;
  }

  bool operator==(const ConstIterator& other) const
  {
    return ( vector == other.vector && index == other.index );
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !(*this == other);
  }

};

template <typename Type>
class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
{
public:
  using pointer = typename Vector::pointer;
  using reference = typename Vector::reference;

  explicit Iterator(){}

  Iterator(const ConstIterator& other) : ConstIterator(other) {}

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

#endif // AISDI_LINEAR_VECTOR_H
