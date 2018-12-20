#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

typedef int Key;
typedef string Val;
const bool RED = 1;
const bool BLACK = 0;

class RedBlackBST
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
			n_color		= color;
			n_counter	= counter;
		}
	public:
		Key n_key;
		Val n_val;
		Node *n_left, *n_right;
		bool n_color;
		int n_counter;
	};

public:
	RedBlackBST();
	~RedBlackBST();

	void put( Key key, Val val );
	int size();
	void print();

private:
	void free( Node *node );
	bool isRed( Node *node );
	Node* put( Node *node, Key key, Val val );

	Node* rotateLeft( Node *node );
	Node* rotateRight( Node *node );
	void flipColor( Node *node );
	int size( Node *node );
	void print( Node *node );

private:
	Node *m_root;

};



#endif //AVL_H