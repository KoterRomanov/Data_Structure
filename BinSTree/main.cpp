#include "BinSTree.h"


int main( int argc, char **argv )
{
	BinSTree bst;
	bst.put( 1, 100 );
	bst.put( 2, 200 );
	bst.put( 3, 300 );
	bst.put( 4, 400 );
	bst.put( 5, 500 );

	bst.DLRPrint();

	cout << bst.treeDepth() << endl;

	system("pause");
	return 0;
}