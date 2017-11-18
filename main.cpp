#include <iostream>
#include <string>
#include <iomanip> //setw setfill
#include <windows.h>  //system
#include <fstream>
#include "AddBook.h"
#include "Record.h"
using namespace std;

void ShowBackground(); //进入界面
void Exit(); //退出界面
void showMailList(const AddBook& Add); //通讯录界面
void add(AddBook& Add); //添加联系人
void del(AddBook& Add); //删除联系人
void Change(AddBook& Add); //修改联系人信息
void Over(AddBook& Add); //清除通讯录

int main(void)
{
    Record re1, re2, re3, re4;
    ifstream infile;
    infile.open("input.txt");
    infile>>re1>>re2>>re3>>re4;
//    Record re1("郭孟然", "16122131", "18817619557", "18817619557@163.com");
//    Record re2("张思远", "66666666", "66666666666", "666666666@gmail.com");
//    Record re3("王程锦", "77777777", "77777777777", "77777777777@126.com");
//    Record re4("吴天元", "88888888", "88888888888", "888888888888@qq.com");
    Record re[4] = {re1, re2, re3, re4};
    AddBook Add(re, 4);
    Add.Sort(); //按照字母表排序

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
            case '1': add(Add); break;    //添加新成员
            case '2': del(Add); break;    //删除指定姓名的成员
            case '3': Change(Add); break; //修改指定姓名成员的数据
            case '4': Over(Add); break;   //清空通讯录
            case '0': judge = false; Exit(); break;
            default : break;              //回到主菜单
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
    cout<<'*'<<setw(17)<<' '<<"欢迎使用通讯录"<<setw(18)<<'*'<<endl;
    cout<<'*'<<setw(49)<<'*'<<endl;
    cout<<'*'<<setw(49)<<'*'<<endl;
    cout<<setfill('*')<<setw(50)<<'*'<<endl;
    cout<<"请选择输入 1--查看当前的全部联系人   0--退出通讯录"<<endl<<endl;
    cout<<"请按照功能提示输入:  ";
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
    cout<<setfill(' ')<<setw(24)<<' '<<"通讯录"<<setw(24)<<' '<<endl;
    cout<<" "<<setfill('-')<<setw(54)<<'-'<<endl;
    cout<<"| "<<"姓名"<<"  |   "<<"学号"<<"   |    "<<"电话"<<"     |"<<setfill(' ')<<setw(8)<<" "<<"邮箱"<<setw(9)<<" "<<"|"<<endl;
    Add.ShowEverything();
    cout<<endl<<"请选择输入:  1--添加新的成员   2--删除指定姓名的成员"<<endl;
    cout<<endl<<setfill(' ')<<setw(13)<<' '<<"3--修改指定姓名成员的数据 4--清空通讯录"<<endl<<endl;
    cout<<setfill(' ')<<setw(13)<<' '<<"0--退出通讯录"<<endl<<endl;
    cout<<"请按照功能提示输入:  ";
}

void add(AddBook& Add)
{
    system("cls");
    cout<<"请依次输入新成员的姓名, 学号, 电话号码，邮箱"<<endl<<endl;
    cout<<"请按照提示输入：";
    string new1, new2, new3, new4;
    cin>>new1>>new2>>new3>>new4;  //***
    Add.AddNewPerson(new1, new2, new3, new4);
    Add.Sort();  //排序
}

void del(AddBook& Add)
{
    system("cls");
    cout<<"请输入要删除的成员的姓名"<<endl<<endl;
    cout<<"请按照提示输入：";
    string dename;
    cin>>dename;
    Add.DeletePerson(dename);
}

void Change(AddBook& Add)
{
    system("cls");
    cout<<"请输入要修改的成员的姓名: ";
    string changename;
    cin>>changename;
    cout<<endl<<"请选择要修改的信息种类： 1--学号  2--电话  3--邮箱"<<endl<<endl;
    cout<<"请按照功能提示输入: ";
    char choose;
    cin>>choose;
    switch(choose)
    {
        case '1':
            {
                cout<<endl<<"请输入修改后的学号 ";
                string Stnum;
                cin>>Stnum;
                Add.ChangeStudentNumber(changename, Stnum);
                break;
            }
        case '2':
            {
                cout<<endl<<"请输入修改后的电话 ";
                string Phone;
                cin>>Phone;
                Add.ChangePhone(changename, Phone);
                break;
            }
        case '3':
            {
                cout<<endl<<"请输入修改后的邮箱 ";
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

