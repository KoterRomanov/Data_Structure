#include "avl.h"

RedBlackBST::RedBlackBST()
	:m_root(NULL)
{

}

RedBlackBST::~RedBlackBST()
{
	free( m_root );
}

void RedBlackBST::free( Node *node )
{
	if( NULL == node ) return;

	free( node->n_left );
	free( node->n_right );

	delete node;
	node = NULL;
}

void RedBlackBST::put( Key key, Val val )
{
	m_root = put( m_root, key, val );
}

//添加新键
RedBlackBST::Node* RedBlackBST::put( Node *node, Key key, Val val )
{
	if( NULL == node ) return new Node( key, val, 1, RED );

	if( key < node->n_key )			node->n_left	= put( node->n_left, key, val );
	else if( key > node->n_key )	node->n_right	= put( node->n_right, key, val );
	else							node->n_val		= val;

	//处理旋转和颜色转换
	if( isRed( node->n_right ) && !isRed( node->n_left ) )			node = rotateLeft( node );
	if( isRed( node->n_left )  && isRed( node->n_left->n_left ) )	node = rotateRight( node );
	if( isRed( node->n_left )  && isRed( node->n_right ) )			flipColor( node );

	node->n_counter = size( node->n_left ) + size( node->n_right ) + 1;
	return node;
}

//检测节点颜色
bool RedBlackBST::isRed( Node *node )
{
	if( NULL == node ) return false;
	return node->n_color;
}

//左旋转
RedBlackBST::Node* RedBlackBST::rotateLeft( Node *node )
{
	Node *right			= node->n_right;
	node->n_right		= right->n_left;
	right->n_left		= node;

	right->n_color		= node->n_color;
	node->n_color		= RED;
	right->n_counter	= node->n_counter;
	node->n_counter		= size( node->n_left ) + size( node->n_right ) + 1;

	return right;
}

//右旋转
RedBlackBST::Node* RedBlackBST::rotateRight( Node *node )
{ 
	Node *left		= node->n_left;
	node->n_left	= left->n_right;
	left->n_right	= node;
	left->n_color	= node->n_color;
	node->n_color	= RED;
	left->n_counter = node->n_counter;
	node->n_counter = size( node->n_left ) + size( node->n_right ) + 1;
	return left;
}

//颜色转换
void RedBlackBST::flipColor( Node *node )
{
	node->n_color	= RED;
	node->n_left	= BLACK;
	node->n_right	= BLACK;
}

int RedBlackBST::size()
{
	return size( m_root );
}

int RedBlackBST::size( Node *node )
{
	if( NULL == node ) return 0;
	return node->n_counter;
}

void RedBlackBST::print()
{
	print( m_root );
}

void RedBlackBST::print( Node *node )
{
	if( NULL == node )	return;

	print( node->n_left );
	cout << node->n_val << endl;
	print( node->n_right );
}
