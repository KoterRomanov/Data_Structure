#include "avl.h"

int main( int argc, char **argv )
{
	AVLTree tree;
	tree.insertNode( 1, "1" );
	tree.insertNode( 77, "77" );
	tree.insertNode( 57, "57" );

	system( "pause" );
	return 0;
}