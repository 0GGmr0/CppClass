#ifndef LINKLIST_H
#define LINKLIST_H

#include <iomanip>
#include <fstream>
//class AddBook;  //避免.h文件互相include

template <typename T>
class LinkList;   //提前申明


//Node类
template <typename T>
class Node
{
public:
	//声明友元类
	friend class LinkList<T>;
	friend class AddBook;
	Node();
	Node(const T& Data); 	//构造函数，为结点赋值
	void ChangeData(const Node<T>& node);
    void NodeOutput();
private:
	Node *next;
	T data;

};

template <typename T>
Node<T>::Node() {}


template <typename T>   //对Node的结点赋值
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


//LinkList类
template <typename T>
class LinkList
{
public:
	LinkList();							// 默认的构造函数
	LinkList(const T* t, const int& n);	// 把一系列连续的数据(数组元素)存入链表中
	LinkList(const LinkList<T>& List);	// 拷贝构造链表
	LinkList<T> & operator=(const LinkList<T>& List);		// 赋值运算
	virtual ~LinkList();				// 析构函数（虚函数）
	void DeleteCurNode();				// 删除当前结点,然后cur_node的值会变成其原来前一个的值
	void FreeList();					// 释放所有结点
	void ShowCurData() const;			// 输出当前结点数据
	void ShowList() const;				// 输出所有结点数据
//	Node<T>* GoTop();					// 绝对位置：首结点
//	Node<T>* Go(const int& n) ;			// 绝对位置：第 n(从 0 起)个结点,如果超出链表范围则返回最后一个非零结点
//	Node<T>* GoBottom();				// 绝对位置：尾结点
//	Node<T>* Skip(const int& n = 1);    // 相对定位：偏移 n (可为负数)个结点
//	bool isEmpty() const;				// 当前链表是否为空链表
//	bool isBegin() const;				// 当前结点是否为首结点
//	bool isLast() const;				// 当前结点是否为尾结点
//	T& CurData() const;				    // 引用返回当前结点本身
//	int  CurPos() const;				// 返回当前结点序号。0 为首结点，-1 无当前结点
//	int  NumNodes() const;				// 返回当前链表结点数

protected:
	Node<T> *head;  //链表头
	Node<T> *cur_node;  //当前结点,在之后的函数中做返回值用，很方便
	int num; //链表结点数
};


template <typename T>
LinkList<T>::LinkList()  //默认构造函数
{
	num = 0;
	head = NULL;
	cur_node = NULL;
}

template <typename T>
LinkList<T>::LinkList(const T* t,const int& n)  //把一系列连续的数据(数组元素)存入链表中
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
LinkList<T>::LinkList(const LinkList<T>& List) //拷贝构造列表
{
	//此处应注意拷贝从List的头部开始拷贝，所以不能用往头部添加元素的方法，必须从尾部开始添加
	num = List.num;
	if (num == 0)  //如果List为空链表
	{
		head = NULL;
		cur_node = NULL;
		return;
	}
	Node<T> *p, *ptail, *temp = List.head;
	head = ptail =  new Node<T>(List.head->data); //为头部赋值,并且让ptail和head的初始值相同
	if (List.head == List.cur_node)
		cur_node = head;
	for (int i = 1; i < num; i++)
	{
		temp = temp->next;
		p = new Node<T>(temp->data);  //p每次都指的都是ptail的下一个结点
		if (temp == List.cur_node) //放在循环里寻找cur_node的好处是可以不用创建新的空间来储存
			cur_node = p;
		ptail->next = p;  //让ptail和p连接起来
		ptail = p;  // 让ptail变成当前p的位置
	}
	ptail->next = NULL;
}

template <typename T>
LinkList<T> & LinkList<T>::operator=(const LinkList<T>& List)  //重载赋值运算符，步骤和拷贝构造列表相似
{
    if (this == &List) //避免对自己赋值
		return *this;
	FreeList(); //将原来链表中的内容全部释放
	num = List.num;
	if (num == 0)  //如果List为空链表
	{
		head = NULL;
		cur_node = NULL;
		return *this;
	}
	Node<T> *p, *ptail, *temp = List.head;
	head = new Node<T>(List.head->data); //为头部赋值
	ptail = head;  //让ptail初始时和head相同
	if (List.head == List.cur_node)
		cur_node = head;
	for (int i = 1; i < num; i++)
	{
		temp = temp->next;
		p = new Node<T>(temp->data);  //p每次都指的都是ptail的下一个结点
		if (temp == List.cur_node) //放在循环里寻找cur_node的好处是可以不用创建新的空间来储存
			cur_node = p;
		ptail->next = p;  //让ptail和p连接起来
		ptail = p;  // 让ptail变成当前p的位置
	}
	ptail->next = NULL;
	return *this;
}

template <typename T>
LinkList<T>::~LinkList()  //析构函数
{
	FreeList();
}

template <typename T>
void LinkList<T>::DeleteCurNode()	// 删除当前结点,然后cur_node的值会变成其原来前一个的值
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
void LinkList<T>::FreeList()  //将链表清空
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
void LinkList<T>::ShowCurData() const			// 输出当前结点数据
{
	if (cur_node != NULL)
		cout << cur_node->data;  //会调用Record的重载输出流的函数
}

template <typename T>
void LinkList<T>::ShowList() const          // 输出所有结点数据
{

	Node<T> *p = head;
	ofstream outfile("output.txt");
    outfile<<setfill(' ')<<setw(24)<<' '<<"通讯录"<<setw(24)<<' '<<endl;
    outfile<<" "<<setfill('-')<<setw(54)<<'-'<<endl;
    outfile<<"| "<<"姓名"<<"  |   "<<"学号"<<"   |    "<<"电话"<<"     |"<<setfill(' ')<<setw(8)<<" "<<"邮箱"<<setw(9)<<" "<<"|"<<endl;

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
//Node<T>* LinkList<T>::GoTop()  // 绝对位置：首结点
//{
//	return cur_node = head;
//}
//
//template <typename T>
//Node<T>* LinkList<T>::Go(const int& n)  // 绝对位置：第 n(从 0 起)个结点,如果超出链表范围则返回NULL
//{
//
//	for (int i = 0; i < n && cur_node != NULL; i++)
//		cur_node = cur_node->next;
//	return cur_node;
//}
//
//template <typename T>
//Node<T>* LinkList<T>::GoBottom()// 绝对位置：尾结点
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
//Node<T>* LinkList<T>::Skip(const int& n)			// 相对定位：偏移 n (可为负数)个结点
//{
//	int i;
//	if (n > 0)
//		for (int i = 0; i < n && cur_node != NULL; i++)
//			cur_node = cur_node->next;
//	else if (n < 0)
//	{
//		int SerialNumber = CurPos() + n;
//		cur_node = (SerialNumber < 0) ? NULL : Go(SerialNumber);  //如果是负数且小于0，就返回NULL；否则返回第m个结点(从0开始算)
//	}
//	return cur_node;
//}
//
//template <typename T>
//bool LinkList<T>::isEmpty() const				// 当前链表是否为空链表
//{
//	return head == NULL;
//}
//
//template <typename T>
//bool LinkList<T>::isBegin() const				// 当前结点是否为首结点
//{
//	return cur_node == head;
//}
//
//template <typename T>
//bool  LinkList<T>::isLast() const				// 当前结点是否为尾结点
//{
//	return cur_node->next == NULL;
//}
//
//template <typename T>
//T& LinkList<T>::CurData() const				// 引用返回当前结点本身
//{
//	return cur_node->data;
//}
//
//template <typename T>
//int LinkList<T>::CurPos() const				// 返回当前结点序号。0 为首结点，-1 无当前结点
//{
//	Node<T> *p = head;
//	int judge = 0; //判断是否有结点,如果有结点则记录结点的位置
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
//int LinkList<T>::NumNodes() const     // 返回当前链表结点数
//{
//	return num;
//}

#endif
