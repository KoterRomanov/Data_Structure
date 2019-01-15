#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>

typedef int Key;
typedef int Val;

enum COLOR { RED, BLACK };

//�����
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
	Key n_key;//��
	Val n_val;//ֵ
	COLOR n_color;//��ɫ
	Node *n_left, *n_right;//�����ӽ��
	Node *n_parent;//���ڵ�
};

//�������
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void insertNode( Key key, Val val );//�����½��

private:
	Node* rotateLeft( Node *node );//����ת
	Node* rotateRight( Node *node );//����ת

	Node* insert( Node *node, Key key, Val val );//�����½��

	void free( Node *node );//�ͷ���ռ���ڴ�ռ�

private:
	Node *m_root;
};


#endif //REDBLACKTREE_H