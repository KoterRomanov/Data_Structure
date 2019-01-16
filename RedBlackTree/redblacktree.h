#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>

typedef int Key;
typedef int Val;

const bool BLACK = 0;
const bool RED   = 1;

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
	bool n_color;//颜色
	Node *n_left, *n_right;//左右子结点
};

//红黑树类
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void insertNode( Key key, Val val );//插入新结点
	void deletNode( Key key );//删除键值为key的结点
	Val getNode( Key key );//获取键值为key的结点的值
	void deletMinNode();//删除键值最小结点
	void deletMaxNode();//删除键值最大结点

private:
	Node* insert( Node *node, Key key, Val val );//插入新结点
	Node* delet( Node *node, Key key );//删除给定键值结点
	Val get( Node *node, Key key );//获取给定键值结点
	
	Node* deletMin( Node *node );//删除给定结点子树键值最小结点
	Node* deletMax( Node *node );//删除给定结点子树键值最大结点
	Node* rotateLeft( Node *node );//左旋转
	Node* rotateRight( Node *node );//右旋转
	Node* moveRedLeft( Node *node );
	Node* moveRedRight( Node *node );
	Node* balance( Node *node );//平衡给定子树
	Node* min( Node *node );//获取给定结点子树中键值最小结点
	bool isRed( Node *node );//结点颜色是否为红色
	void flipColor( Node *node );//颜色转换
	

	void free( Node *node );//释放树占用内存空间

private:
	Node *m_root;
};


#endif //REDBLACKTREE_H
