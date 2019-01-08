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
  void DLRPrint();//前序遍历
  void LDRPrint();//中序遍历
  void LRDPrint();//后序遍历
  
private:
  void free( Node *node );
  int get( Node *node, int key );
  Node* put( Node *node, int key, int val );
  Node* min( Node *node );
  Node* deletMin( Node *node );
  
  void DLRPrint( Node *node );//前序遍历
  void LDRPrint( Node *node );//中序遍历
  void LRDPrint( Node *node );//后序遍历
  
private:
  Node *m_root;
  
};

#endif //BINSTREE_H
