#include "avl.h"

int main( int argc, char **argv )
{
	RedBlackBST avl;

	avl.put( 'A', "A" );
	avl.put( 'C', "C" );
	avl.put( 'E', "E" );
	avl.put( 'H', "H" );
	avl.put( 'L', "L" );
	avl.put( 'M', "M" );
	avl.put( 'P', "P" );
	avl.put( 'R', "R" );
	avl.put( 'S', "S" );
	avl.put( 'X', "X" );
	avl.print();

	system( "pause" );
	return 0;
}