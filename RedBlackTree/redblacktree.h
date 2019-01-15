#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>

typedef int Key;
typedef int Val;

enum COLOR { RED, BLACK };

//结点类
class Node
{
public:
	Node( Key key, Val val, bool color )
	{
		n_key = key;
		n_val = val;
		n_color = color;
		n_left = n_right = NULL;
	}

public:
	Key n_key;//键
	Val n_val;//值
	COLOR n_color;//颜色
	Node *n_left, *n_right;//左右子结点
	Node *n_parent;//父节点
};

//红黑树类
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void insertNode( Key key, Val val );//插入新结点

private:
	Node* rotateLeft( Node *node );//左旋转
	Node* rotateRight( Node *node );//右旋转

	Node* insert( Node *node, Key key, Val val );//插入新结点

	void free( Node *node );//释放树占用内存空间

private:
	Node *m_root;
};


#endif //REDBLACKTREE_H