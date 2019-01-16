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
	node->n_left = x->n_right;
	x->n_right = node;
	x->n_color = node->n_color;
	x->n_right->n_color = RED;
	
	return x;
}

Node* RedBlackTree::moveRedLeft( Node *node )
{
	flipColor( node );
	if ( isRed( node->n_right->n_left ) ) {
		node->n_right = rotateRight( node->n_right );
		node = rotateLeft( node );
		flipColor( node );
	}

	return node;
}

Node* RedBlackTree::moveRedRight( Node *node )
{
	flipColor( node );
	if ( isRed(node->n_left->n_left ) ) {
		node = rotateRight( node );
		flipColor( node );
	}

	return node;
}

Node* RedBlackTree::balance( Node *node )
{
	if ( isRed( node->n_right ) ) node = rotateLeft( node );
	if ( isRed( node->n_left ) && isRed( node->n_left->n_left ) ) node = rotateRight( node );
	if ( isRed( node->n_left ) && isRed( node->n_right ) ) flipColor( node );

	return node;
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
	if ( NULL == node )		return new Node( key, val, RED );

	if ( key < node->n_key )		node->n_left = insert( node->n_left, key, val );
	else if ( key > node->n_key )	node->n_right = insert( node->n_right, key, val );
	else 	node->n_val = val;
	
	if ( isRed(node->n_right) && !isRed(node->n_left) )		
		node = rotateLeft( node );
	if ( isRed(node->n_left) && isRed(node->n_left->n_left) )	
		node = rotateRight( node );
	if ( isRed(node->n_left) && isRed(node->n_right) )			
		flipColor( node );
	
	return node;
}

void RedBlackTree::deletMinNode()
{
	if ( !isRed(m_root->n_left) && !isRed(m_root->n_right) )
		m_root->n_color = RED;

	m_root = deletMin( m_root );
	if ( NULL != m_root ) m_root->n_color = BLACK;
}

Node* RedBlackTree::deletMin( Node *node )
{
	if ( NULL == node->n_left ) return NULL;

	if ( !isRed(node->n_left) && !isRed(node->n_left->n_left) )
		node = moveRedLeft( node );

	node->n_left = deletMin( node->n_left );
	return balance( node );
}

void RedBlackTree::deletMaxNode()
{
	if ( !isRed(m_root->n_left) && !isRed(m_root->n_right) )
		m_root->n_color = RED;

	m_root = deletMax( m_root );
	if ( NULL != m_root ) m_root->n_color = BLACK;
}

Node* RedBlackTree::deletMax( Node *node )
{
	if ( isRed( node->n_left ) )
		node = rotateRight( node );

	if ( NULL == node->n_right )
		return NULL;

	if ( !isRed(node->n_right) && !isRed(node->n_left) )
		node = moveRedRight( node );

	node->n_right = deletMax( node->n_right );
	return balance( node );
}

Node* RedBlackTree::min( Node *node )
{
	if ( NULL == node->n_left ) return node;
	else return min( node->n_left );
}

void RedBlackTree::deletNode( Key key )
{
	if ( !isRed(m_root->n_right) && !isRed(m_root->n_left) )
		m_root->n_color = RED;

	m_root = delet( m_root, key );
	if ( NULL != m_root ) m_root->n_color = BLACK;
}

Node* RedBlackTree::delet( Node *node, Key key )
{
	if ( key < node->n_key ) {
		if ( !isRed(node->n_left) && !isRed(node->n_right) )
			node = moveRedLeft( node );
		node->n_left = delet( node->n_left, key );
	}
	else {
		if ( isRed(node->n_left) )
			node = rotateRight( node );

		if ( key == node->n_key && NULL == node->n_right )
			return NULL;

		if ( !isRed(node->n_right) && !isRed(node->n_right->n_left) )
			node = moveRedRight( node );

		if ( key == node->n_key ) {
			Node *x = min( node->n_right );
			node->n_key = x->n_key;
			node->n_val = x->n_val;
			node->n_right = deletMin( node->n_right );
		}
		else node->n_right = delet( node->n_right, key );
	}

	return balance( node );
}