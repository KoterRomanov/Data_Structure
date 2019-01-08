#include "BinSTree.h"

BinSTree::BinSTree()
	:m_root(NULL)
{
}

BinSTree::~BinSTree()
{
  free( m_root );
}

//删除树
void BinSTree::free( Node *node )
{
   if( NULL == node ) return;
   
   free( node->m_left );
   free( node->m_right );
   delete node;
   node = NULL;
}

//查找键值
int BinSTree::get( int key )
{
  return get( m_root, key ); 
}

//查找键值
int BinSTree::get( Node *node, int key )
{
  if( node == NULL )  return NULL;
  
  if( key > node->m_key )       return get( node->m_right, key );
  else if( key < node->m_key )  return get( node->m_left, key );
  else                          return node->m_val;
}

//插入结点
void BinSTree::put( int key, int val )
{
  m_root = put( m_root, key, val ); 
}

//插入结点
Node* BinSTree::put( Node *node, int key, int val )
{
    if ( NULL == node ) return new Node( key, val );
  
	if( key > node->m_key )       node->m_right = put( node->m_right, key, val );
	else if( key < node->m_key )  node->m_left = put( node->m_left, key, val );
    else                          node->m_val = val;
  
    return node;
}

//删除结点
void BinSTree::delet( int key )
{
  m_root = delet( m_root, key ); 
}

//删除结点
Node* BinSTree::delet( Node *node, int key )
{
  if( NULL == node )  return NULL;
  
  if( key > node->m_key ) node->m_right = delet( node->m_right, key );//向右查找
  else if( key < node->m_key ) node->m_left = delet( node->m_left, key );//向左查找
  else {
    //已找到结点并删除
    //1.左、右结点为空(从逻辑上来说这行代码可省略)
    if( NULL == node->m_left && NULL == node->m_right ) return NULL;
    
    //2.只有左结点
    if( NULL == node->m_left ) {
      Node *tmp = node->m_right;
      delete node;
      node = NULL;
      return tmp;
    }
    
    //3.只有右结点
    if( NULL == node->m_right ) {
      Node *tmp = node->m_left;
      delete node;
      node = NULL;
      return tmp;
    }
    
    //4.左、右结点都存在
    Node *tmp = node;
    node = min( tmp->m_right );//找到右子结点中最小结点
    node->m_right = deletMin( tmp->m_right );//连接右结点
    node->m_left = tmp->m_left;//连接左结点
    delete tmp;
    tmp = NULL;
  }
  
  return node;
}

//查找最小结点
Node* BinSTree::min( Node *node )
{
  if( NULL == node->m_left )  return node;
  
  return min( node->m_left );
}

//移除最小结点
Node* BinSTree::deletMin( Node *node )
{
  if( NULL == node->m_left )  return node->m_right;
  node->m_left = deletMin( node->m_left );
  
  return node;
}

//前序遍历
void BinSTree::DLRPrint()
{
  DLRPrint( m_root );  
}

//前序遍历
void BinSTree::DLRPrint( Node *node )
{
  if( NULL == node )  return;
  printf( "Key:%d Val:%d\n", node->m_key, node->m_val );
  DLRPrint( node->m_left );
  DLRPrint( node->m_right );
}

//中序遍历
void BinSTree::LDRPrint()
{
  LDRPrint( m_root );
}

//中序遍历
void BinSTree::LDRPrint( Node *node )
{
  if( NULL == node )  return;
  LDRPrint( node->m_left );
  printf( "Key:%d Val:%d\n", node->m_key, node->m_val );
  LDRPrint( node->m_right );
}

//后序遍历
void BinSTree::LRDPrint()
{
  LRDPrint( m_root );
}

//后序遍历
void BinSTree::LRDPrint( Node *node )
{
  if( NULL == node )  return;
  
  LRDPrint( node->m_left );
  LRDPrint( node->m_right );
  printf( "Key:%d Val:%d\n", node->m_key, node->m_val );
}

//计算树的高度
int BinSTree::treeDepth()
{
	return treeDepth( m_root );
}

int BinSTree::treeDepth( Node *node )
{
	if ( NULL == node )	return 0;
	
	int leftDepth = treeDepth( node->m_left );
	int rightDepth = treeDepth( node->m_right );

	return ( leftDepth > rightDepth )? (leftDepth+1):(rightDepth+1);
}