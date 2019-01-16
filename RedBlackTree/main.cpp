#include "redblacktree.h"

int main( int argc, char **argv )
{
	RedBlackTree tree;

	tree.insertNode( 1, 1 );
	tree.insertNode( 2, 2 );
	tree.insertNode( 3, 3 );
	tree.insertNode( 4, 4 );
	tree.insertNode( 5, 5 );
	tree.insertNode( 6, 6 );
	tree.insertNode( 7, 7 );
	tree.insertNode( 8, 8 );
	tree.insertNode( 9, 9 );


	tree.deletNode( 6 );

	return 0;
}