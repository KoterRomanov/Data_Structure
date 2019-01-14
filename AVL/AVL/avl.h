#ifndef AVL_H
#define AVL_H

/*******************************************************
                      平衡二叉树
*******************************************************/

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

typedef int Key;
typedef string Val;

class AVLTree
{
	class Node
	{
	public:
		Node( Key key, Val val )
		{
			n_key		= key;
			n_val		= val;
			n_left		= NULL;
			n_right		= NULL;
			n_degree	= 1;
		}
		
	public:
		Key n_key;//结点的键
		Val n_val;//结点的值
		Node *n_left, *n_right;//左子结点、右子结点
		int n_degree;//结点的度
	};

public:
	AVLTree();
	~AVLTree();

	void insertNode( Key key, Val val );//插入结点
	void deleteNode( Key key );//删除结点
	Val getNode( Key key );//获取结点的值
	
private:
	Node* leftRotate( Node *node );//左旋转
	Node* rightRotate( Node *node );//右旋转
	Node* leftLeftRotate( Node *node );//LL
	Node* rightRightRotate( Node *node );//RR
	Node* leftRightRotate( Node *node );//LR
	Node* rightLeftRotate( Node *node );//RL
	Node* minNode( Node *node );//node子树中键最小的结点
	Node* maxNode( Node *node );//node子树中键最大的结点
	
	Node *insert( Node *node, Key key, Val val );//插入新结点
	Node *delet( Node *node, Key key );//删除键为key的结点
	
	Val getNode( Node *node, Key key );//获取结点值
	int degree( Node *node );//计算node结点的度
	void free( Node *node );//释放树占用内存空间
	
	void DLROrder( Node *node );//前序遍历
	void LDROrder( Node *node );//中序遍历
	void LRDOrder( Node *node );//后序遍历
	
private:
	Node *m_root;//root node//根结点
};
#endif //AVL_H
