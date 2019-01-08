#ifndef BINSTREE_H
#define BINSTREE_H

#include <iostream>

using std::cout;
using std::endl;

struct Node
{
  Node( int key, int val ) :m_key(key),n_val(val), m_left(NULL), m_right(NULL){}
  
  Node *m_left, *m_right;
  int m_key, m_val;
};

class BinSTree
{
public:
  BinSTree();
  ~BinSTree();
  
  int get( int key );
  void put( int key, int val );
  void delet( int key );
  
private:
  void free( Node *node );
  int get( Node *node, int key );
  Node* put( Node *node, int key, int val );
  Node* min( Node *node );
  Node* deletMin( Node *node );
  
private:
  Node *m_root;
  
};

#endif //BINSTREE_H
