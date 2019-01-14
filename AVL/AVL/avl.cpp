#include "avl.h"

//平衡二叉树构造函数
AVLTree::AVLTree()
  :m_root(NULL)
{
    
}

//平衡二叉树析构函数
AVLTree::~AVLTree()
{
    free( m_root );
}

//释放树占用的内存空间
void AVLTree::free( Node *node )
{
    if( NULL == node )  return;
    free( node->n_left );
    free( node->n_right );
    
    delete node;
    node = NULL;
}

//计算结点的高度
int AVLTree::calDegree( Node *node )
{
    if( NULL == node ) return 0;
    int leftChildDegree = calDegree( node->n_left );
    int rightChildDegree = calDegree( node->n_right );
    
    return ( leftChildDegree > rightChildDegree )? (leftChildDegree+1):(rightChildDegree+1);
}

//获取结点的高度
int AVLTree::getDegree( Node *node )
{
	if ( NULL == node )	return 0;
	return node->n_degree;
}

//左旋转
AVLTree::Node* AVLTree::leftRotate( Node *node )
{
    Node *tmp = node->n_right;
    node->n_right = tmp->n_left;
    tmp->n_left = node;
    
    tmp->n_degree = calDegree( tmp );
    node->n_degree = calDegree( node );
    
    return tmp;
}

//右旋转
AVLTree::Node* AVLTree::rightRotate( Node *node )
{
    Node *tmp = node->n_left;
    node->n_left = tmp->n_right;
    tmp->n_right = node;
    
    tmp->n_degree = calDegree( tmp );
    node->n_degree = calDegree( node );
    
    return tmp;
}

//LL
AVLTree::Node* AVLTree::leftLeftRotate( Node *node )
{
    return rightRotate( node );
}

//RR
AVLTree::Node* AVLTree::rightRightRotate( Node *node )
{
    return leftRotate( node );
}

//LR
AVLTree::Node* AVLTree::leftRightRotate( Node *node )
{
    node->n_left = leftRotate( node->n_left );
    return rightRotate( node );
}

//RL
AVLTree::Node* AVLTree::rightLeftRotate( Node *node )
{
    node->n_right = rightRotate( node->n_right );
    return leftRotate( node );
}

//添加结点
void AVLTree::insertNode( Key key, Val val )
{
    m_root = insert( m_root, key, val );   
}

//删除结点
void AVLTree::deleteNode( Key key )
{
    m_root = delet( m_root, key );   
}

//获取node子树中键最大结点
AVLTree::Node* AVLTree::minNode( Node *node )
{
    if( NULL == node->n_left )  return node;
    return minNode( node->n_left );
}

//获取node子树中键最小结点
AVLTree::Node* AVLTree::maxNode( Node *node )
{
    if( NULL == node->n_right ) return node;
    return maxNode( node->n_right );
}

//添加结点
AVLTree::Node* AVLTree::insert( Node *node, Key key, Val val )
{
    if( NULL == node )  return new Node( key, val );
    
    if( key < node->n_key ) {
    //插入左子树
    	node->n_left = insert( node->n_left, key, val );
		node->n_degree = calDegree( node );//计算结点的高度
        if( getDegree(node->n_left) - getDegree(node->n_right) == 2 ) { 
            //左树失衡
            if( key < node->n_left->n_key ) {
                //LL
                node = leftLeftRotate( node );
            }
            else {
                //LR
                node = leftRightRotate( node );
            }
        }
    }
    else if( key > node->n_key ) {
        //插入右子树
        node->n_right = insert( node->n_right, key, val );
		node->n_degree = calDegree( node );//计算结点的高度
        if( getDegree(node->n_right) - getDegree(node->n_left ) == 2 ) {
            //右树失衡
            if( key > node->n_right->n_key ) {
		//RR
                node = rightRightRotate( node );
            }
            else {
                //RL
                node = rightLeftRotate( node );
            }
        }
    }
    else {
        //修改键值
        node->n_val = val;
    }
    
    return node;         
}

//删除结点
AVLTree::Node* AVLTree::delet( Node *node, Key key )
{
    if( NULL == node )  return NULL;
    if( key < node->n_key ) {
        //待删除结点在左子树
        node->n_left = delet( node->n_left, key );
		node->n_degree = calDegree( node );//计算结点的高度
        //删除左子树结点后，检查右子树是否失衡
        if( getDegree(node->n_right) - getDegree(node->n_left) == 2 ) {
			Node *rightNode = node->n_right;
			//判断子树失衡为左还是右
			if( getDegree(rightNode->n_left) >= get(rightNode->n_right) ) { //当左右高度相等时,按照RR情况处理
            	//RR
            	node = rightRightRotate( node );
        	}
        	else {
            	//RL
            	node = rightLeftRotate( node );
			}
        }
    }
    else if( key >node->n_key ) {
        //待删除结点在右子树
        node->n_right = delet( node->n_right, key );
		node->n_degree = calDegree( node );//计算结点的高度
        //删除右子树结点后，检查左子树是否失衡
        if( getDegree(node->n_left) - getDegree(node->n_right) == 2 ) {
			Node *leftNode = node->n_left;
			if( getDegree(leftNode->n_left) >= getDegree(rightNode->n_right) ) { //当左右高度相等,按照LL情况处理
            	//LL
            	node = leftLeftRotate( node );
        	}
        	else {
            	//LR
            	node = leftRightRotate( node );
			}
        }
    }
    else { //找到待删除结点分为4种情况
        /* 1.待删除结点不存在左右子结点（则该结点为叶子结点,直接删除待删除结点）
        /  2.待删除结点存在左子结点 & 不存在右子结点（使用待删除结点的左结点替换待删除结点位置,然后删除待删除结点）
        /  3.待删除结点存在右子结点 & 不存在左子结点（使用待删除结点的右结点替换待删除结点位置,然后删除待删除结点）
        /  4.待删除结点存在左右子结点（若左子树度大于右子树,则查找左子树中键最大结点替换待删除结点位置;
                                  反之,则查找右子树中键最小结点替换待删除结点位置。始终删除结点多的一边） */
        if( NULL != node->n_left && NULL != node->n_right ) {
            //situation 4
            if( getDegree(node->n_left) > getDegree(node->n_right) ) {
                //待删除结点左子树高于右子树
                Node *max = maxNode( node->n_left );
                node->n_key = max->n_key;
                node->n_val = max->n_val;
                node->n_left = delet( node->n_left, max->n_key );
				node->n_degree = calDegree( node );//计算结点的高度
            }
            else {
                //待删除结点右子树高于或等于左子树
                Node *min = minNode( node->n_right );
                node->n_key = min->n_key;
                node->n_val = min->n_val;
                node->n_right = delet( node->n_right, min->n_key );
				node->n_degree = calDegree( node );//计算结点的高度
            }
        }
        else {
            //situation 1 & 2 & 3
            Node *tmp = node;
            node = ( NULL == tmp->n_left )? tmp->n_right:tmp->n_left;
            delete tmp;
            tmp = NULL;
        }
    }
   
    return node;
}
           
//前序遍历           
void AVLTree::DLROrder( Node *node )
{
    cout << node->n_key <<endl;
    DLROrder( node->n_left );
    DLROrder( node->n_right );
}

//中序遍历           
void AVLTree::LDROrder( Node *node )
{
    LDROrder( node->n_left );
    cout << node->n_key << endl;
    LDROrder( node->n_right );
}

//后序遍历           
void AVLTree::LRDOrder( Node *node )
{
    LRDOrder( node->n_left );
    LRDOrder( node->n_right );
    cout << node->n_key << endl;
}

//根据键获取结点的值
Val AVLTree::getNode( Key key )
{
    return getNode( m_root, key );
}
      
//根据键获取结点的值
Val AVLTree::getNode( Node *node, Key key )
{
    if( key < node->n_key ) return getNode( node->n_left, key );
    else if( key > node->n_key ) return getNode( node->n_right, key );
    else return node->n_val;
}
           
           
/*
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
*/
