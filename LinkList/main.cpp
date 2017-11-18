#include <iostream>
#include <string>
#include <iomanip> //setw setfill
#include <windows.h>  //system
#include <fstream>
#include "AddBook.h"
#include "Record.h"
using namespace std;

void ShowBackground(); //�������
void Exit(); //�˳�����
void showMailList(const AddBook& Add); //ͨѶ¼����
void add(AddBook& Add); //�����ϵ��
void del(AddBook& Add); //ɾ����ϵ��
void Change(AddBook& Add); //�޸���ϵ����Ϣ
void Over(AddBook& Add); //���ͨѶ¼

int main(void)
{
    Record re1, re2, re3, re4;
    ifstream infile;
    infile.open("input.txt");
    infile>>re1>>re2>>re3>>re4;
//    Record re1("����Ȼ", "16122131", "18817619557", "18817619557@163.com");
//    Record re2("��˼Զ", "66666666", "66666666666", "666666666@gmail.com");
//    Record re3("���̽�", "77777777", "77777777777", "77777777777@126.com");
//    Record re4("����Ԫ", "88888888", "88888888888", "888888888888@qq.com");
    Record re[4] = {re1, re2, re3, re4};
    AddBook Add(re, 4);
    Add.Sort(); //������ĸ������

    char choose;
    bool judge = true;
	ShowBackground();
	cin>>choose;
    if(choose != '1')
    {
        Exit();
        return 0;
    }
    else
    {
        while(true)
        {
            if(judge == false)
                break;
            system("cls");
            showMailList(Add);
            cin>>choose;
            switch(choose)
            {
            case '1': add(Add); break;    //����³�Ա
            case '2': del(Add); break;    //ɾ��ָ�������ĳ�Ա
            case '3': Change(Add); break; //�޸�ָ��������Ա������
            case '4': Over(Add); break;   //���ͨѶ¼
            case '0': judge = false; Exit(); break;
            default : break;              //�ص����˵�
            }
        }
    }
	return 0;
}


void ShowBackground()
{
    cout<<setfill('*')<<setw(50)<<'*'<<endl;
    cout<<'*'<<setfill(' ')<<setw(49)<<'*'<<endl;
    cout<<'*'<<setw(49)<<'*'<<endl;
    cout<<'*'<<setw(17)<<' '<<"��ӭʹ��ͨѶ¼"<<setw(18)<<'*'<<endl;
    cout<<'*'<<setw(49)<<'*'<<endl;
    cout<<'*'<<setw(49)<<'*'<<endl;
    cout<<setfill('*')<<setw(50)<<'*'<<endl;
    cout<<"��ѡ������ 1--�鿴��ǰ��ȫ����ϵ��   0--�˳�ͨѶ¼"<<endl<<endl;
    cout<<"�밴�չ�����ʾ����:  ";
}

void Exit()
{
    system("cls");
    cout<<setfill('*')<<setw(50)<<'*'<<endl;
    cout<<setfill(' ');
    cout<<'*'<<setw(49)<<'*'<<endl;
    cout<<'*'<<setw(49)<<'*'<<endl;
    cout<<'*'<<setw(20)<<" "<<"Good Bye"<<setw(21)<<'*'<<endl;
    cout<<'*'<<setw(49)<<'*'<<endl;
    cout<<'*'<<setw(49)<<'*'<<endl;
    cout<<setfill('*')<<setw(50)<<'*'<<endl;
}

void showMailList(const AddBook& Add)
{
    system("cls");
    cout<<setfill(' ')<<setw(24)<<' '<<"ͨѶ¼"<<setw(24)<<' '<<endl;
    cout<<" "<<setfill('-')<<setw(54)<<'-'<<endl;
    cout<<"| "<<"����"<<"  |   "<<"ѧ��"<<"   |    "<<"�绰"<<"     |"<<setfill(' ')<<setw(8)<<" "<<"����"<<setw(9)<<" "<<"|"<<endl;
    Add.ShowEverything();
    cout<<endl<<"��ѡ������:  1--����µĳ�Ա   2--ɾ��ָ�������ĳ�Ա"<<endl;
    cout<<endl<<setfill(' ')<<setw(13)<<' '<<"3--�޸�ָ��������Ա������ 4--���ͨѶ¼"<<endl<<endl;
    cout<<setfill(' ')<<setw(13)<<' '<<"0--�˳�ͨѶ¼"<<endl<<endl;
    cout<<"�밴�չ�����ʾ����:  ";
}

void add(AddBook& Add)
{
    system("cls");
    cout<<"�����������³�Ա������, ѧ��, �绰���룬����"<<endl<<endl;
    cout<<"�밴����ʾ���룺";
    string new1, new2, new3, new4;
    cin>>new1>>new2>>new3>>new4;  //***
    Add.AddNewPerson(new1, new2, new3, new4);
    Add.Sort();  //����
}

void del(AddBook& Add)
{
    system("cls");
    cout<<"������Ҫɾ���ĳ�Ա������"<<endl<<endl;
    cout<<"�밴����ʾ���룺";
    string dename;
    cin>>dename;
    Add.DeletePerson(dename);
}

void Change(AddBook& Add)
{
    system("cls");
    cout<<"������Ҫ�޸ĵĳ�Ա������: ";
    string changename;
    cin>>changename;
    cout<<endl<<"��ѡ��Ҫ�޸ĵ���Ϣ���ࣺ 1--ѧ��  2--�绰  3--����"<<endl<<endl;
    cout<<"�밴�չ�����ʾ����: ";
    char choose;
    cin>>choose;
    switch(choose)
    {
        case '1':
            {
                cout<<endl<<"�������޸ĺ��ѧ�� ";
                string Stnum;
                cin>>Stnum;
                Add.ChangeStudentNumber(changename, Stnum);
                break;
            }
        case '2':
            {
                cout<<endl<<"�������޸ĺ�ĵ绰 ";
                string Phone;
                cin>>Phone;
                Add.ChangePhone(changename, Phone);
                break;
            }
        case '3':
            {
                cout<<endl<<"�������޸ĺ������ ";
                string Mail;
                cin>>Mail;
                Add.ChangeMail(changename, Mail);
                break;
            }
        default: break;
    }
}

void Over(AddBook& Add)
{
    Add.FreeList();
}

