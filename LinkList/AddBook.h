
#ifndef ADDBOOK_H
#define ADDBOOK_H

#include "Record.h"
#include "LinkList.h"
#include <string>
#include <iostream>
using namespace std;


class AddBook :public LinkList<Record>
{
public:
	AddBook();			//默认构造函数
	AddBook(const Record *Re, const int& n);   //构造函数,把n个t[i]放进链表
	AddBook(const AddBook& Add);		//拷贝构造函数
	virtual ~AddBook();				//析构函数
    void AddNewPerson(const string& Name = "", const string& Stnum = "", const string& Phone = "", const string& Mail = ""); //添加一个新的成员
	Node<Record>* Find(const string& Name);     //查询通讯录的用户
	void DeletePerson(const string& Name);  //删除此名字联系人
	void ShowEverything() const;  //输出通讯录中所有的结点
	void Sort(); //按照字母表从小到大排序
	void ChangeStudentNumber(const string& Name, const string& Stnum = ""); //修改学号
	void ChangePhone(const string& Name, const string& Stnum = "");//修改电话
	void ChangeMail(const string& Name, const string& Stnum = ""); //修改邮箱
};


AddBook::AddBook() : LinkList() {}  //默认构造函数

AddBook::AddBook(const Record *Re, const int& n) :LinkList(Re, n){}  //构造函数,把n个t[i]放进链表

AddBook::AddBook(const AddBook& Add) :LinkList(Add) {}  //拷贝构造函数

AddBook::~AddBook() {}  //析构函数

Node<Record>* AddBook::Find(const string& Name)  //查找通讯录中某人的信息
{
	cur_node = head;
	while (cur_node != NULL)
	{
		if (cur_node->data.name == Name)
			return cur_node;
		cur_node = cur_node->next;
	}
	cout << "no such name" << endl;
	return cur_node = NULL;
}



void AddBook::AddNewPerson(const string& Name, const string& Stnum, const string& Phone, const string& Mail)
 {
     Record Tail(Name, Stnum, Phone, Mail);
     Node<Record> *tail;
     tail = new Node<Record>(Tail);
     if(head ==  NULL) //如果通讯录是空的
     {
         cur_node = head = tail;
         return;
     }
     cur_node = head;
     while(cur_node->next != NULL)
        cur_node = cur_node->next;
     cur_node->next = tail;
     tail->next = NULL;
     cur_node = head;
     num++;
 }

void AddBook::DeletePerson(const string& Name)   //删除此名字联系人
{
	Find(Name);  //找到当前结点
	DeleteCurNode(); //删除当前结点
}


void AddBook::ShowEverything() const //输出所有结点的数据
{
	ShowList();
}

void AddBook::Sort()  //按照字母表从小到大排序
{
	cur_node = head;
	if (cur_node == NULL)
		return;
	Node<Record> *p = cur_node->next;
	Node<Record> temp = *head; //初始化 这里为什么会出现自赋值情
	for (int i = 0;i < num - 1; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			if (cur_node->data.name > p->data.name)
			{

                temp.ChangeData(*cur_node);
                cur_node->ChangeData(*p);
                p->ChangeData(temp);
			}
            p = p->next;
		}
		cur_node = cur_node->next;
		p = cur_node->next;
	}
}

void AddBook::ChangeStudentNumber(const string& Name, const string& Stnum)  //修改学号
{
    Find(Name);
    cur_node->data.stnum = Stnum;
}
void AddBook::ChangePhone(const string& Name, const string& Phone)  //修改电话
{
    Find(Name);
    cur_node->data.phone = Phone;
}
void AddBook::ChangeMail(const string& Name, const string& Mail) //修改邮箱
{
    Find(Name);
    cur_node->data.mail = Mail;
}
#endif
