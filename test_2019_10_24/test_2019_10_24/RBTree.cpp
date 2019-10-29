#pragma once
enum Color{RED , BLACK};
template <class V>
struct RBTreeNode
{
	RBTreeNode(const V& val, Color color = RED)
	:_pLeft(nullptr)
	, _pRight(nullptr)
	, _pParent(nullptr)
	, _val(val)
	, _color(color)
	{}
	RBTreeNode<V>* _pLeft;
	RBTreeNode<V>* _pRight;
	RBTreeNode<V>* _pParent;
	V _val;
	Color _color;
};
template <class V>
class RBTree
{
	typedef RBTreeNode<V> Node;
public:
	RBTree()
		:_pHead(new Node)
	{
		//将头结点创建好
		_pHead->_pParent = nullptr;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}
	bool Insert(const V& data)//插入
	{
		Node*& pRoot = GetRoot();//获得根结点
		if (nullptr == pRoot)
		{
			pRoot = new Node(data,BLACK);//根结点是黑色的
			pRoot->_pParent = _pHead;
		}
		else
		{
			//按照二叉搜索树的性质插入新的结点
			//1、找待插入结点在二叉搜索树中的位置
			Node* pCur = pRoot;
			Node* pParent = _pHead;
			while (pCur)
			{
				pParent = pCur;
				if (data < pCur->_val)
				{
					pCur = pCur->_pLeft;
				}
				else if (data>pCur->_val)
				{
					pCur = pCur->_pRight;
				}
				else
					return false;
			}
			//插入新结点
			pCur = new Node(data);
			if (data < pParent->_val)
			{
				pParent->_pLeft = pCur;
			}
			else
			{
				pParent->_pRight = pCur;
			}
			pCur->_pParent = pParent;//更新插入结点的双亲


			//如果pParent是红色的，插入的新结点默认颜色也是红色的，违反了红黑树的性质
			while (pParent!=_pHead &&pParent->_color == RED)//要考虑双亲到达根结点的情况，如果是这样，就不需要调整了，因此加上第一个条件
			{
				//分情况讨论
				Node* GrandFather = pParent->_pParent;//先找到祖父结点，这个祖父节点不需要判空，因为双亲节点是红色，而根据红黑树的性质，根结点一定是黑色，因此双亲一定有双亲
				if (pParent == GrandFather->_pLeft)//双亲是祖父的左孩子
				{
					Node* uncle = GrandFather->_pRight;
					//情况1：叔叔结点存在且为红色
					if (uncle&&uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						GrandFather->_color = RED;
						pCur = GrandFather;
						pParent = pCur->_pParent;
					}
					else//剩下情况2和情况3
					{
						//先处理情况3（pCur是双亲的右孩子，叔叔结点可能不存在||存在且为黑色）
						if (pCur = pParent->_pRight)
						{//情况3与情况1的区别在于将情况3以双亲为根结点的子树进行左单旋，然后交换双亲和pCur的位置交换就得到了情况1
							RotateL(pParent);
							swap(pParent, pCur);
						}
						GrandFather->_color = RED;
						pParent->_color = BLACK;
						RotateR(GrandFather);//右单旋完成之后就不需要再继续向上更新了，因为上面是红色或者黑色已经不重要了

					}
				}
				else//双亲是祖父的右孩子
				{

				}


			}

		}
		_pHead->_pLeft = LeftMost();//头结点的_pLeft域指向最小的结点
		_pHead->_pRight = RightMost();//头结点的_pRight域指向最大的节点
		pRoot->_color = BLACK;//将根结点的颜色设置为黑色，因为有可能根节点颜色会改变
		return true;
	}
private:
	void RotateL(Node* pParent)
	{

	}
private:
	Node* LeftMost()
	{
		Node* pCur = GetRoot();//从根结点开始找
		if (nullptr == pCur)
			return _pHead;
		while (pCur->_pLeft)//找最左侧结点
			pCur = pCur->_pLeft;
		return pCur;
	}
	Node* RightMost()
	{
		Node* pCur = GetRoot();
		if (cur == nullptr)
			return _pHead;
		while (pCur->_pRight)
			pCur = pCur->_pRight;
		return pCur;
	}
	Node*& GetRoot()
	{
		return _pHead->_pParent;
	}
private:
	Node* _pHead;//记录头结点即可
};
