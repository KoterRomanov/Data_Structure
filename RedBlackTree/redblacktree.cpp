#include "redblacktree.h"

RedBlackTree::RedBlackTree()
	:m_root(NULL)
{

}

RedBlackTree::~RedBlackTree()
{
	free( m_root );
}

void RedBlackTree::free( Node *node )
{
	if( NULL == node )	return;

	free( node->n_left );
	free( node->n_right );

	delete node;
	node = NULL;
}

Node* RedBlackTree::rotateLeft( Node *node )
{
	if( NULL == node->n_right )	return NULL;

	Node *nodeRight = node->n_right;
	node->n_right = nodeRight->n_left;
	nodeRight->n_left->n_parent = node;
	nodeRight->n_parent = node->n_parent;

	if( NULL == node->n_parent )
		nodeRight->n_parent = NULL;
	else if( node = node->n_parent->n_left )
		node->n_parent->n_left = nodeRight;
	else if( node = node->n_parent->n_right )
		node->n_parent->n_right = nodeRight;

	nodeRight->n_left = node;
	node->n_parent = nodeRight;
}

Node* RedBlackTree::rotateRight( Node *node )
{

}

void RedBlackTree::insertNode( Key key, Val val )
{

}

Node* RedBlackTree::insert( Node *node, Key key, Val val )
{

	return node;
}