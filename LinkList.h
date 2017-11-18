#ifndef LINKLIST_H
#define LINKLIST_H

#include <iomanip>
#include <fstream>
//class AddBook;  //����.h�ļ�����include

template <typename T>
class LinkList;   //��ǰ����


//Node��
template <typename T>
class Node
{
public:
	//������Ԫ��
	friend class LinkList<T>;
	friend class AddBook;
	Node();
	Node(const T& Data); 	//���캯����Ϊ��㸳ֵ
	void ChangeData(const Node<T>& node);
    void NodeOutput();
private:
	Node *next;
	T data;

};

template <typename T>
Node<T>::Node() {}


template <typename T>   //��Node�Ľ�㸳ֵ
Node<T>::Node(const T& Data) :data(Data) {}

template <typename T>
void Node<T>::NodeOutput()
{
    cout<<data<<endl;
}

template <typename T>
void Node<T>::ChangeData(const Node<T>& node)
{
    data = node.data;
}


//template <typename T>
//void Node<T>::ChangeData(const Node<T>* node)
//{
//    data = node->data;
//}


//LinkList��
template <typename T>
class LinkList
{
public:
	LinkList();							// Ĭ�ϵĹ��캯��
	LinkList(const T* t, const int& n);	// ��һϵ������������(����Ԫ��)����������
	LinkList(const LinkList<T>& List);	// ������������
	LinkList<T> & operator=(const LinkList<T>& List);		// ��ֵ����
	virtual ~LinkList();				// �����������麯����
	void DeleteCurNode();				// ɾ����ǰ���,Ȼ��cur_node��ֵ������ԭ��ǰһ����ֵ
	void FreeList();					// �ͷ����н��
	void ShowCurData() const;			// �����ǰ�������
	void ShowList() const;				// ������н������
//	Node<T>* GoTop();					// ����λ�ã��׽��
//	Node<T>* Go(const int& n) ;			// ����λ�ã��� n(�� 0 ��)�����,�����������Χ�򷵻����һ��������
//	Node<T>* GoBottom();				// ����λ�ã�β���
//	Node<T>* Skip(const int& n = 1);    // ��Զ�λ��ƫ�� n (��Ϊ����)�����
//	bool isEmpty() const;				// ��ǰ�����Ƿ�Ϊ������
//	bool isBegin() const;				// ��ǰ����Ƿ�Ϊ�׽��
//	bool isLast() const;				// ��ǰ����Ƿ�Ϊβ���
//	T& CurData() const;				    // ���÷��ص�ǰ��㱾��
//	int  CurPos() const;				// ���ص�ǰ�����š�0 Ϊ�׽�㣬-1 �޵�ǰ���
//	int  NumNodes() const;				// ���ص�ǰ��������

protected:
	Node<T> *head;  //����ͷ
	Node<T> *cur_node;  //��ǰ���,��֮��ĺ�����������ֵ�ã��ܷ���
	int num; //��������
};


template <typename T>
LinkList<T>::LinkList()  //Ĭ�Ϲ��캯��
{
	num = 0;
	head = NULL;
	cur_node = NULL;
}

template <typename T>
LinkList<T>::LinkList(const T* t,const int& n)  //��һϵ������������(����Ԫ��)����������
{
	Node<T> *p;
	head = NULL;
	for (int i = n - 1; i >= 0; i--)
	{
		p = new Node<T>(t[i]);
		p->next = head;
		head = p;
	}
	num = n;
	cur_node = head;
}

template <typename T>
LinkList<T>::LinkList(const LinkList<T>& List) //���������б�
{
	//�˴�Ӧע�⿽����List��ͷ����ʼ���������Բ�������ͷ�����Ԫ�صķ����������β����ʼ���
	num = List.num;
	if (num == 0)  //���ListΪ������
	{
		head = NULL;
		cur_node = NULL;
		return;
	}
	Node<T> *p, *ptail, *temp = List.head;
	head = ptail =  new Node<T>(List.head->data); //Ϊͷ����ֵ,������ptail��head�ĳ�ʼֵ��ͬ
	if (List.head == List.cur_node)
		cur_node = head;
	for (int i = 1; i < num; i++)
	{
		temp = temp->next;
		p = new Node<T>(temp->data);  //pÿ�ζ�ָ�Ķ���ptail����һ�����
		if (temp == List.cur_node) //����ѭ����Ѱ��cur_node�ĺô��ǿ��Բ��ô����µĿռ�������
			cur_node = p;
		ptail->next = p;  //��ptail��p��������
		ptail = p;  // ��ptail��ɵ�ǰp��λ��
	}
	ptail->next = NULL;
}

template <typename T>
LinkList<T> & LinkList<T>::operator=(const LinkList<T>& List)  //���ظ�ֵ�����������Ϳ��������б�����
{
    if (this == &List) //������Լ���ֵ
		return *this;
	FreeList(); //��ԭ�������е�����ȫ���ͷ�
	num = List.num;
	if (num == 0)  //���ListΪ������
	{
		head = NULL;
		cur_node = NULL;
		return *this;
	}
	Node<T> *p, *ptail, *temp = List.head;
	head = new Node<T>(List.head->data); //Ϊͷ����ֵ
	ptail = head;  //��ptail��ʼʱ��head��ͬ
	if (List.head == List.cur_node)
		cur_node = head;
	for (int i = 1; i < num; i++)
	{
		temp = temp->next;
		p = new Node<T>(temp->data);  //pÿ�ζ�ָ�Ķ���ptail����һ�����
		if (temp == List.cur_node) //����ѭ����Ѱ��cur_node�ĺô��ǿ��Բ��ô����µĿռ�������
			cur_node = p;
		ptail->next = p;  //��ptail��p��������
		ptail = p;  // ��ptail��ɵ�ǰp��λ��
	}
	ptail->next = NULL;
	return *this;
}

template <typename T>
LinkList<T>::~LinkList()  //��������
{
	FreeList();
}

template <typename T>
void LinkList<T>::DeleteCurNode()	// ɾ����ǰ���,Ȼ��cur_node��ֵ������ԭ��ǰһ����ֵ
{
	if (head == NULL || cur_node == NULL)
		return;

	if (head == cur_node)
	{
		head = head->next;
		delete cur_node;
		cur_node = head;
		num--;
		return;
	}

	Node<T> *p = head;
	while (p != NULL)
	{
		if (p->next == cur_node)
		{
			p->next = cur_node->next;
			delete cur_node;
			cur_node = p;
			num--;
			return;
		}
		p = p->next;
	}
}

template <typename T>
void LinkList<T>::FreeList()  //���������
{
	Node<T> *p = head;
	while (head != NULL)
	{
		head = head->next;
		delete p;
		p = head;
	}
	cur_node = NULL;
	num = 0;
}

template <typename T>
void LinkList<T>::ShowCurData() const			// �����ǰ�������
{
	if (cur_node != NULL)
		cout << cur_node->data;  //�����Record������������ĺ���
}

template <typename T>
void LinkList<T>::ShowList() const          // ������н������
{

	Node<T> *p = head;
	ofstream outfile("output.txt");
    outfile<<setfill(' ')<<setw(24)<<' '<<"ͨѶ¼"<<setw(24)<<' '<<endl;
    outfile<<" "<<setfill('-')<<setw(54)<<'-'<<endl;
    outfile<<"| "<<"����"<<"  |   "<<"ѧ��"<<"   |    "<<"�绰"<<"     |"<<setfill(' ')<<setw(8)<<" "<<"����"<<setw(9)<<" "<<"|"<<endl;

	while (p != NULL)
	{
	    outfile<<" "<<setfill('-')<<setw(54)<<'-'<<endl;
	    outfile<<"|"<< p->data<<" "<<"|"<<endl;
	    cout<<" "<<setfill('-')<<setw(54)<<'-'<<endl;
		cout <<"|"<< p->data<<" "<<"|"<<endl;
		p = p->next;
	}
	outfile<<" "<<setfill('-')<<setw(54)<<'-'<<endl;
	cout<<" "<<setfill('-')<<setw(54)<<'-'<<endl;
}

//template <typename T>
//Node<T>* LinkList<T>::GoTop()  // ����λ�ã��׽��
//{
//	return cur_node = head;
//}
//
//template <typename T>
//Node<T>* LinkList<T>::Go(const int& n)  // ����λ�ã��� n(�� 0 ��)�����,�����������Χ�򷵻�NULL
//{
//
//	for (int i = 0; i < n && cur_node != NULL; i++)
//		cur_node = cur_node->next;
//	return cur_node;
//}
//
//template <typename T>
//Node<T>* LinkList<T>::GoBottom()// ����λ�ã�β���
//{
//	while (cur_node != NULL)
//	{
//		if (cur_node->next == NULL)
//			break;
//		cur_node = cur_node->next;
//	}
//	return cur_node;
//}
//
//template <typename T>
//Node<T>* LinkList<T>::Skip(const int& n)			// ��Զ�λ��ƫ�� n (��Ϊ����)�����
//{
//	int i;
//	if (n > 0)
//		for (int i = 0; i < n && cur_node != NULL; i++)
//			cur_node = cur_node->next;
//	else if (n < 0)
//	{
//		int SerialNumber = CurPos() + n;
//		cur_node = (SerialNumber < 0) ? NULL : Go(SerialNumber);  //����Ǹ�����С��0���ͷ���NULL�����򷵻ص�m�����(��0��ʼ��)
//	}
//	return cur_node;
//}
//
//template <typename T>
//bool LinkList<T>::isEmpty() const				// ��ǰ�����Ƿ�Ϊ������
//{
//	return head == NULL;
//}
//
//template <typename T>
//bool LinkList<T>::isBegin() const				// ��ǰ����Ƿ�Ϊ�׽��
//{
//	return cur_node == head;
//}
//
//template <typename T>
//bool  LinkList<T>::isLast() const				// ��ǰ����Ƿ�Ϊβ���
//{
//	return cur_node->next == NULL;
//}
//
//template <typename T>
//T& LinkList<T>::CurData() const				// ���÷��ص�ǰ��㱾��
//{
//	return cur_node->data;
//}
//
//template <typename T>
//int LinkList<T>::CurPos() const				// ���ص�ǰ�����š�0 Ϊ�׽�㣬-1 �޵�ǰ���
//{
//	Node<T> *p = head;
//	int judge = 0; //�ж��Ƿ��н��,����н�����¼����λ��
//	while (p != NULL)
//	{
//		if (p == cur_node)
//			return judge;
//		p = p->next;
//		judge++;
//	}
//	return -1;
//}
//
//template <typename T>
//int LinkList<T>::NumNodes() const     // ���ص�ǰ��������
//{
//	return num;
//}

#endif
