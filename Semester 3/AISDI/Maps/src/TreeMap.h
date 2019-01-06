#ifndef AISDI_MAPS_TREEMAP_H
#define AISDI_MAPS_TREEMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <algorithm>

namespace aisdi
{

template <typename KeyType, typename ValueType>
class TreeMap
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
  class Node;

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  friend class ConstIterator;

  TreeMap() : root(nullptr)
  {}

  TreeMap(std::initializer_list<value_type> list)
  {

    root = nullptr;
    for(auto it = list.begin(); it != list.end(); ++it){
      operator[](it->first) = it->second;
    }
  }

  TreeMap(const TreeMap& other)
  {
    root = nullptr;
    for(auto it = other.begin(); it != other.end(); ++it){
      operator[](it->first) = it->second;
    }
  }

  TreeMap(TreeMap&& other) : TreeMap()
  {
    *this = std::move(other);
  }

  ~TreeMap(){
    if(root) {
        recursive_delete(*root);
        root = nullptr;
    }
  }

  TreeMap& operator=(const TreeMap& other)
  {
    if(*this == other){
        return *this;
    }
    this->TreeMap::~TreeMap();
    for(auto it = other.begin(); it != other.end(); ++it){
      operator[](it->first) = it->second;
    }
    return *this;
  }

  TreeMap& operator=(TreeMap&& other)
  {
    if(*this == other){
      return *this;
    }
    this->TreeMap::~TreeMap();
    std::swap(root, other.root);
    return *this;
  }

  bool isEmpty() const
  {
    return !root;
  }

  mapped_type& operator[](const key_type& key)
  {
    Node *node = findNode(key);
    if(!node){
      //create
      node = new Node(new value_type( key, mapped_type() ), nullptr);
      if(!root){//if map is empty => simply add
        root = node;
      }
      else {
        addBalance(root, node);
      }
    }
    return node->value->second;
  }

  const mapped_type& valueOf(const key_type& key) const
  {
      return val_of(key);
  }

  mapped_type& valueOf(const key_type& key)
  {
      return val_of(key);
  }

  const_iterator find(const key_type& key) const
  {
      return ConstIterator(this, findNode(key));
  }

  iterator find(const key_type& key)
  {
      return Iterator(ConstIterator(this, findNode(key)));
  }

  Node *findNode(const key_type& key) const{
      for(auto node = root; node != nullptr; ){
          if(node->value->first == key){
              return node;
          }
          node = ( key < node->value->first) ? node->left : node->right;
      }
      return nullptr;
  }

  void remove(const key_type& key)
  {
    remove(findNode(key));
  }

  void remove(const const_iterator& it)
  {
    remove(it.node);
  }

  size_type getSize() const
  {
    return isEmpty() ? 0 : root->getSize();
  }

  bool operator==(const TreeMap& other) const
  {
    auto it2 = other.begin();
    for(auto it1 = begin(); it1!=end(); ++it1, ++it2){
      if(it2 == other.end() || *it1 != *it2){
        return false;
      }
    }
    return ( it2 == other.end() );
  }

  bool operator!=(const TreeMap& other) const
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
    Node *node = root;
    if(root) {
      try {
        while (true) {
          node = ++(*node); //throws exception on
        }
      }
      catch (...) {}
    }
    return ConstIterator(this, node);
  }

  const_iterator cend() const
  {
    return ConstIterator(this, nullptr);
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

  TreeMap(Node *root_) :root(root_){}

  mapped_type& val_of(const key_type& key) const{
    for(auto node = root; node != nullptr; ){
      if(node->value->first == key){
        return node->value->second;
      }
      node = ( key < node->value->first) ? node->left : node->right;
    }
    throw std::out_of_range("Not found");
  }

  void recursive_delete(Node &node){
    //delete left child if exists
    try{
      recursive_delete(*(++node)); //operator++ throws on nullptr
    }
    catch(...){}

    //delete right child if exists
    try{
        recursive_delete(*(node++));
    }
    catch(...){}

    //delete myself
    delete &node;
  }

  void remove(Node *node){
    if(!node){
      throw std::out_of_range("Not found");
    }
    Node *future = nullptr, *toAdd = nullptr;

    try{
      if((++(*node))->length > ((*node)++)->length){
        future = ++(*node);
        toAdd = (*node)++;
      }
      else{
        future = (*node)++;
        toAdd = ++(*node);
      }
    }
    catch(bool isLeftNull){
      try{
        future = (isLeftNull) ? (*node)++ : ++(*node);
        toAdd = nullptr;
      }
      catch(bool){//both are null
        future = nullptr;
        toAdd = nullptr;
      }
    }
    //change pointers and add left/right to tree
    if(node == root){
      root = future;
      if(root){
          root->parent = nullptr;
      }
      addBalance(toAdd, nullptr);
    }
    else{
      if(!(node->parent)){
        throw std::runtime_error("Node has no parent");
      }
      if(node->parent->left == node){
        node->parent->left = future;
      }
      else {
        node->parent->right = future;
      }

      if(future){
        future->parent = node->parent;
        addBalance(toAdd, nullptr);
      }
    }
    //delete node
    delete node;
    //set size and balance
    if(root) {
        addBalance(root, nullptr);
    }
  }

  Node *last() const{
    //search for last element
    Node *node = root;
    if(root) {
      try {
        while (true) {
          node = (*node)++; //throws exception on
        }
      }
      catch (bool) {}
    }
    return node;
  }

  void addBalance(Node *node, Node *toAdd){
    if(!node){
        return ;
    }
    if(!toAdd){
      //only balance
      try {
        addBalance(++(*node), nullptr);
      }
      catch(bool){}

      try {
        addBalance((*node)++, nullptr);
      }
      catch(bool){}
    }
    else {
      KeyType key = toAdd->value->first;
      try {
        addBalance((key < node->value->first) ? ++(*node) : (*node)++, toAdd);
      }
      catch (bool willBeLeftChild) {
        //I am leaf => balance
        if (toAdd) {
          //add
          if (willBeLeftChild) {
            node->left = toAdd;
          }
          else{
            node->right = toAdd;
          }
          toAdd->parent = node;
          //balance subtree
          addBalance(toAdd, nullptr);
        }

      }
    }

    node->countLength();
    node->countSize();

    //balance
    while(true){
      if(node->getLeftLength() - node->getRightLength() > 1){
          if(node->left->isRightHeavy()){
              rotate(node->left, true);
              rotate(node, false);
          }
          else{
              rotate(node, false);
          }
      }
      else if(node->getRightLength() - node->getLeftLength() > 1){
        if(node->right->isLeftHeavy()){
            rotate(node->right, false);
            rotate(node, true);
        }
        else{
            rotate(node, true);
        }
      }
      else{
        break;
      }
    }

  }

  void rotate(Node *root, bool leftFlag){
    Node *pivot = leftFlag ? root->right : root->left;
    Node *parent = root->parent;
    Node *b;


    if(!pivot){
      throw std::runtime_error("No pivot in rotating");
    }

    //set new parent
    if(!parent){
      pivot->parent = nullptr;
    }
    else {
      bool isLeftChild = root->parent->left == root;
      pivot->parent = parent;

      if(isLeftChild){
        parent->left = pivot;
      }
      else {
        parent->right = pivot;
      }
    }

    if(leftFlag) {
      //a = pivot->right;
      b = pivot->left;
      //c = root->left;

      pivot->left = root;
      //pivot->right = a;
      root->right = b;
      //root->left = c;
    }
    else{
      //a = pivot->left;
      b = pivot->right;
      //c = root->right;

      pivot->right = root;
      //pivot->left = a;
      root->left = b;
      //root->right = c;
    }

    root->countLength();
    pivot->countLength();

    root->countSize();
    pivot->countSize();

    if(root == this->TreeMap::root){
      this->TreeMap::root = pivot;
    }
  }


  //fields
  Node *root;
};

template <typename KeyType, typename ValueType>
class TreeMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename TreeMap::const_reference;
  using value_type = typename TreeMap::value_type;
  using pointer = const typename TreeMap::value_type*;

  friend class TreeMap;

  explicit ConstIterator(TreeMap<KeyType, ValueType> const *map_, Node *node_) : map(map_), node(node_)
  {}

  ConstIterator(const ConstIterator& other)
  {
    map = other.map;
    node = other.node;
  }

  ConstIterator& operator++()
  {
    if(*this == map->end()){
      throw std::out_of_range("Incrementing end");
    }
    try{
      node = (*node)++; //throws bool if n++ is null
      node = (new TreeMap <KeyType,ValueType> (node) )->begin().node;
    }
    catch(bool){//no right child
      while(true){
        try{
          node = (*node)--;//right parent
          break;
        }
        catch(bool){//no right parent
          try{
            node = --(*node); //left parent
          }
          catch(bool){//no right child, no left and right parent
            node = nullptr;
            break;
          }
        }
      }
    }
    return *this;
  }

  ConstIterator operator++(int)
  {
    auto tmp = *this;
    operator++();
    return tmp;
  }

  ConstIterator& operator--()
  {
    if(*this == map->begin()){
      throw std::out_of_range("Decrementing begin");
    }

    if(*this == map->end()){
      node = map->last();
    }
    else {
      try {
        node = ++(*node);
      }
      catch (bool) {
        //hasn't got right child => means that is begin
        try {
          while (true) {
            node = (*node)--;
          }
        }
        catch (bool) {
          try {
            //reversed right child
            node = --(*node);
            return *this;
          }
          catch (bool) {
            //no parent => was begin => error
            throw std::out_of_range("Decrementing begin");
          }
        }
      }


      node = (new TreeMap<KeyType, ValueType>(node))->last();
    }
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
      throw std::out_of_range("Dereferencing end");
    }
    return **node;
  }

  pointer operator->() const
  {
    return &this->operator*();
  }

  bool operator==(const ConstIterator& other) const
  {
    return other.node == node;
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !(*this == other);
  }

private:
    TreeMap const *map;
    Node *node;
};

template <typename KeyType, typename ValueType>
class TreeMap<KeyType, ValueType>::Iterator : public TreeMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename TreeMap::reference;
  using pointer = typename TreeMap::value_type*;

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

template <typename KeyType, typename ValueType>
class TreeMap<KeyType, ValueType>::Node{
    using reference = typename TreeMap::Node&;
    using value_type = typename TreeMap::value_type;
    using pointer = typename TreeMap::Node*;

    friend class TreeMap;
public:

    Node(value_type *value_, pointer parent_)
            : value(value_), parent(parent_), left(nullptr), right(nullptr), length(1), size(1) {}

    ~Node(){
      delete value;
    }

    const Node *getParent() const {
      return parent;
    }

    void setParent(const Node *parent) {
      Node::parent = parent;
    }

    value_type &operator*() const{
      return *value;
    }

    value_type *operator->() const
    {
      return &this->operator*();
    }

    size_t getLength() const {
      return length;
    }

    void setLength(size_t length) {
      Node::length = length;
    }

    pointer operator++(){
      //preincrementation = ++node = node->left
      if(!left){
        throw true;
      }
      return left;
    }

    pointer operator++(int){
      //postincrementation = node++ = node->right
      if(!right){
        throw false;
      }
      return right;
    }

    pointer operator--(){
      //left parent or throw true
      //predecrementation = --node
      if(!parent || parent->right != this){
        throw true;
      }
      return parent;
    }

    pointer operator--(int){
      //right parent or throw false
      //postdecrementation = node--
      if(!parent || parent->left != this){
        throw false;
      }
      return parent;
    }

    bool isLeftChild(){
      if(parent == nullptr){
        return false;
      }
      return parent->left == *this;
    }

    size_t getSize() const {
      return size;
    }

    bool isRightHeavy() const {
        return getRightLength() - getLeftLength() > 0;
    }

    bool isLeftHeavy() const {
        return getLeftLength() - getRightLength() > 0;
    }

    int getLeftLength() const {
      return (left) ? left->length : 0;
    }

    int getRightLength() const {
      return (right) ? right->length : 0;
    }

    int getLeftSize() const {
      return (left) ? left->size : 0;
    }

    int getRightSize() const {
      return (right) ? right->size : 0;
    }

    void countLength(){
      //use carefully only if you set correctly children lengths!!!
      length = std::max( getLeftLength(), getRightLength() ) + 1;
    }

    void countSize(){
      //use carefully only if you set correctly children sizes!!!
      size = getLeftSize() + getRightSize() + 1;
    }



private:
    value_type *value;
    pointer parent, left, right;
    size_t length, size;
};


}
#endif /* AISDI_MAPS_MAP_H */
