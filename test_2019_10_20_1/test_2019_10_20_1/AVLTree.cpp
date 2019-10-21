#include<iostream>
using namespace std;
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _pLeft;
	AVLTreeNode<K, V>* _pRight;
	AVLTreeNode<K, V>* _pParent;
	pair<K, V> _data;
	int _bf;
	AVLTreeNode(const pair<K,V>& data)
		: _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _data(data)
		, _bf(0)
	{}
};
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		: _pRoot(NULL)
	{}
	bool Insert(const pair<K,V>& data)
	{
		if (NULL == _pRoot)
		{
			_pRoot = new Node(data);
			return true;
		}
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		while (pCur)
		{
			if (data.first < pCur->_data.first){
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (data.first > pCur->_data.first){
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
				return false;
		}
		pCur = new Node(data);
		if (data.first < pParent->_data.first)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		pCur->_pParent = pParent;

		while (pParent)
		{
			if (pParent->_pLeft == pCur)
				pParent->_bf--;
			else
				pParent->_bf++;
			if (0 == pParent->_bf)
				return true;
			else if (-1 == pParent->_bf || 1 == pParent->_bf){
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else{
				if (2 == pParent->_bf){
					if (1 == pCur->_bf)
						RotatoL(pParent);
					else
						RotatoRL(pParent);
				}
				else{
					if (-1 == pCur->_bf)
						RotatoR(pParent);
					else
						RotatoLR(pParent);
				}
				break;
			}
		}
		return true;
	}
	void InOrder()
	{
		cout << "InOrder:";
		_InOrder(_pRoot);
		cout << endl;
	}
private:
	//ÓÒµ¥Ðý
	void RotatoR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;
		pSubL->_pRight = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;
		if (NULL == pPParent){
			_pRoot = pSubL;
			pSubL->_pParent = NULL;
		}
		else{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
		pParent->_bf = pSubL->_bf = 0;
	}
	//×óµ¥Ðý
	void RotatoL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		pSubR->_pParent = pPParent;
		if (NULL == pPParent){
			_pRoot = pSubR;
			pSubR->_pParent = NULL;
		}
		else{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
		pParent->_bf = pSubR->_bf = 0;
	}
	//×óÓÒË«Ðý×ª
	void RotatoLR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;
		RotatoL(pParent->_pLeft);
		RotatoR(pParent);
		if (1 == bf)
			pSubL->_bf = -1;
		else if (-1 == bf)
			pParent->_bf = 1;

	}
	//ÓÒ×óË«Ðý×ª
	void RotatoRL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;
		RotatoR(pParent->_pRight);
		RotatoL(pParent);
		if (1 == bf)
			pParent->_bf = -1;
		else if (-1 == bf)
			pSubR->_bf = 1;
	}
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data.first << " ";
			_InOrder(pRoot->_pRight);
		}
	}
private:
	Node* _pRoot;
};
void testAVLTree()
{
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> t;
	for (auto e : arr)
		t.Insert(make_pair(e, e));
	t.InOrder();
}
int main()
{
	testAVLTree();
	return 0;
}