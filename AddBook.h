
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
	AddBook();			//Ĭ�Ϲ��캯��
	AddBook(const Record *Re, const int& n);   //���캯��,��n��t[i]�Ž�����
	AddBook(const AddBook& Add);		//�������캯��
	virtual ~AddBook();				//��������
    void AddNewPerson(const string& Name = "", const string& Stnum = "", const string& Phone = "", const string& Mail = ""); //���һ���µĳ�Ա
	Node<Record>* Find(const string& Name);     //��ѯͨѶ¼���û�
	void DeletePerson(const string& Name);  //ɾ����������ϵ��
	void ShowEverything() const;  //���ͨѶ¼�����еĽ��
	void Sort(); //������ĸ���С��������
	void ChangeStudentNumber(const string& Name, const string& Stnum = ""); //�޸�ѧ��
	void ChangePhone(const string& Name, const string& Stnum = "");//�޸ĵ绰
	void ChangeMail(const string& Name, const string& Stnum = ""); //�޸�����
};


AddBook::AddBook() : LinkList() {}  //Ĭ�Ϲ��캯��

AddBook::AddBook(const Record *Re, const int& n) :LinkList(Re, n){}  //���캯��,��n��t[i]�Ž�����

AddBook::AddBook(const AddBook& Add) :LinkList(Add) {}  //�������캯��

AddBook::~AddBook() {}  //��������

Node<Record>* AddBook::Find(const string& Name)  //����ͨѶ¼��ĳ�˵���Ϣ
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
     if(head ==  NULL) //���ͨѶ¼�ǿյ�
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

void AddBook::DeletePerson(const string& Name)   //ɾ����������ϵ��
{
	Find(Name);  //�ҵ���ǰ���
	DeleteCurNode(); //ɾ����ǰ���
}


void AddBook::ShowEverything() const //������н�������
{
	ShowList();
}

void AddBook::Sort()  //������ĸ���С��������
{
	cur_node = head;
	if (cur_node == NULL)
		return;
	Node<Record> *p = cur_node->next;
	Node<Record> temp = *head; //��ʼ�� ����Ϊʲô������Ը�ֵ��
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

void AddBook::ChangeStudentNumber(const string& Name, const string& Stnum)  //�޸�ѧ��
{
    Find(Name);
    cur_node->data.stnum = Stnum;
}
void AddBook::ChangePhone(const string& Name, const string& Phone)  //�޸ĵ绰
{
    Find(Name);
    cur_node->data.phone = Phone;
}
void AddBook::ChangeMail(const string& Name, const string& Mail) //�޸�����
{
    Find(Name);
    cur_node->data.mail = Mail;
}
#endif
