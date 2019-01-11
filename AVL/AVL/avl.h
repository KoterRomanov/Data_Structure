#ifndef AVL_H
#define AVL_H

/*******************************************************
                      平衡二叉树
*******************************************************/

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

typedef int Key;
typedef string Val;
const bool RED = 1;
const bool BLACK = 0;

class AVLTree
{
	class Node
	{
	public:
		Node( Key key, Val val, int counter, bool color )
		{
			n_key		= key;
			n_val		= val;
			n_left		= NULL;
			n_right		= NULL;
			n_degree	= 0;
		}
	public:
		Key n_key;//node key
		Val n_val;//nodde value
		Node *n_left, *n_right;//left and right child
		int n_degree;//node degree
	};

public:
	AVLTree();
	~AVLTree();

	void insertNode( Key key, Val val );
	void deleteNode( Key key );
	
private:
	Node* leftLeftRotate( Node *node );//LL
	Node* rightRightRotate( Node *node );//RR
	Node* leftRightRotate( Node *node );//LR
	Node* rightLeftRotate( Node *node );//RL
	
	Node *insert( Node *node, Key key, Val val );
	Node *delet( Node *node, Key key );
	
	void print( Node *node );//print tree
	void free( Node *node );//free tree
private:
	Node *m_root;//root node
};
#endif //AVL_H
