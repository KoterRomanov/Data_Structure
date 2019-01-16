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

bool RedBlackTree::isRed( Node *node )
{
	if ( NULL == node )	return false;
	return node->n_color == RED;
}

Node* RedBlackTree::rotateLeft( Node *node )
{
	Node *x = node->n_right;
	node->n_right = x->n_left;
	x->n_left = node;
	x->n_color = node->n_color;
	x->n_left->n_color = RED;
	
	return x;
}

Node* RedBlackTree::rotateRight( Node *node )
{
	Node *x = node->n_left;
	node->n_left = x->right;
	x->n_left = node;
	x->n_color = node->n_color;
	x->n_left->n_color = RED;
	
	return x;
}

Node* RedBlackTree::moveRedLeft( Node *node )
{
}

Node* RedBlackTree::moveRedRight( Node *node )
{
}

Node* RedBlackTree::balance( Node *node )
{
}
void RedBlackTree::flipColor( Node *node )
{
	node->n_color = !node->n_color;
	node->n_left->n_color = !node->n_left->n_color;
	node->n_right->n_color = !node->n_right->n_color;
}

Val RedBlackTree::getNode( Key key )
{
	return get( m_root, key );
}

Val RedBlackTree::get( Node *node, Key key )
{
	if ( NULL == node )	return NULL;
	if ( key > node->n_key )	return get( node->n_right, key );
	else if ( key < node->n_key )	return get( node->n_left, key );
	
	return node->n_val;
}

void RedBlackTree::insertNode( Key key, Val val )
{
	m_root = insert( m_root, key, val );
	m_root->n_color = BLACK;
}

Node* RedBlackTree::insert( Node *node, Key key, Val val )
{
	if ( NULL == node )	return new Node( key, val, RED );
	if ( key < node->n_key )	node->n_left = insert( node->n_left, key, val );
	else if ( key > node->n_key )	node->n_right = insert( node->n_right, key, val );
	else 	node->n_val = val;
	
	if ( !isRed(node->n_right) && !isRed(node->n_left) )	node = rotateLeft( node );
	if ( ifRed(node->n_left) && isRed(node->n_left->n_left) )	node = rotateRight( node );
	if ( isRed(node->n_left) && isRed(node->n_right) )	flipColor( node );
	
	return node;
}
