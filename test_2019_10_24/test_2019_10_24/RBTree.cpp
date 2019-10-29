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
		//��ͷ��㴴����
		_pHead->_pParent = nullptr;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}
	bool Insert(const V& data)//����
	{
		Node*& pRoot = GetRoot();//��ø����
		if (nullptr == pRoot)
		{
			pRoot = new Node(data,BLACK);//������Ǻ�ɫ��
			pRoot->_pParent = _pHead;
		}
		else
		{
			//���ն��������������ʲ����µĽ��
			//1���Ҵ��������ڶ����������е�λ��
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
			//�����½��
			pCur = new Node(data);
			if (data < pParent->_val)
			{
				pParent->_pLeft = pCur;
			}
			else
			{
				pParent->_pRight = pCur;
			}
			pCur->_pParent = pParent;//���²������˫��


			//���pParent�Ǻ�ɫ�ģ�������½��Ĭ����ɫҲ�Ǻ�ɫ�ģ�Υ���˺����������
			while (pParent!=_pHead &&pParent->_color == RED)//Ҫ����˫�׵�������������������������Ͳ���Ҫ�����ˣ���˼��ϵ�һ������
			{
				//���������
				Node* GrandFather = pParent->_pParent;//���ҵ��游��㣬����游�ڵ㲻��Ҫ�пգ���Ϊ˫�׽ڵ��Ǻ�ɫ�������ݺ���������ʣ������һ���Ǻ�ɫ�����˫��һ����˫��
				if (pParent == GrandFather->_pLeft)//˫�����游������
				{
					Node* uncle = GrandFather->_pRight;
					//���1�������������Ϊ��ɫ
					if (uncle&&uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						GrandFather->_color = RED;
						pCur = GrandFather;
						pParent = pCur->_pParent;
					}
					else//ʣ�����2�����3
					{
						//�ȴ������3��pCur��˫�׵��Һ��ӣ���������ܲ�����||������Ϊ��ɫ��
						if (pCur = pParent->_pRight)
						{//���3�����1���������ڽ����3��˫��Ϊ��������������������Ȼ�󽻻�˫�׺�pCur��λ�ý����͵õ������1
							RotateL(pParent);
							swap(pParent, pCur);
						}
						GrandFather->_color = RED;
						pParent->_color = BLACK;
						RotateR(GrandFather);//�ҵ������֮��Ͳ���Ҫ�ټ������ϸ����ˣ���Ϊ�����Ǻ�ɫ���ߺ�ɫ�Ѿ�����Ҫ��

					}
				}
				else//˫�����游���Һ���
				{

				}


			}

		}
		_pHead->_pLeft = LeftMost();//ͷ����_pLeft��ָ����С�Ľ��
		_pHead->_pRight = RightMost();//ͷ����_pRight��ָ�����Ľڵ�
		pRoot->_color = BLACK;//����������ɫ����Ϊ��ɫ����Ϊ�п��ܸ��ڵ���ɫ��ı�
		return true;
	}
private:
	void RotateL(Node* pParent)
	{

	}
private:
	Node* LeftMost()
	{
		Node* pCur = GetRoot();//�Ӹ���㿪ʼ��
		if (nullptr == pCur)
			return _pHead;
		while (pCur->_pLeft)//���������
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
	Node* _pHead;//��¼ͷ��㼴��
};
