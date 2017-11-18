
#ifndef RECORD_H
#define RECORD_H
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

//通讯录有姓名，学号， 电话， 邮件
class Record
{
public:
	friend class AddBook;
	friend ofstream& operator << (ofstream& fileout, const Record& rec);  //重载文件写入
	friend ifstream& operator >> (ifstream& filein, Record& rec);  //重载文件读取
	friend istream& operator >> (istream& in, Record& rec);  //重载输入流函数
	friend ostream& operator << (ostream& out, const Record& rec);  //重载输出流函数
	Record(const string& Name ="",const string& Stnum ="",const string& Phone= "",const string& Mail = "");  //构造函数
	Record(const Record& rec);  //拷贝构造函数

	//Record& operator=(const Record& re2);  //重载赋值运算符

private:
	string name;  //名字
	string stnum; //学号
	string phone; //电话
	string mail;  //邮件
};

//构造函数
Record::Record(const string& Name,const string& Stnum, const string& Phone, const string& Mail) :name(Name), stnum(Stnum), phone(Phone), mail(Mail) {}

//转换构造函数
Record::Record(const Record& rec) :name(rec.name), stnum(rec.stnum), phone(rec.phone), mail(rec.mail) {}

ofstream& operator << (ofstream& fileout, const Record& rec)
{
    fileout <<setfill(' ')<< left<<setw(6) << rec.name << " "<<"|"<<" "<<left<<setw(8)<< rec.stnum
	 << " "<<"|"<<" " <<left<<setw(11)<< rec.phone << " "<<"|"<<" " <<left<<setw(19)<< rec.mail;
	return fileout;
}

//重载输入运算符函数
ifstream& operator >> (ifstream& filein, Record& rec)
{
	filein >> rec.name >> rec.stnum >> rec.phone >> rec.mail;
	return filein;
}

//重载输出运算符函数
ostream& operator<<(ostream& out, const Record& rec)
{
	out <<setfill(' ')<< left<<setw(6) << rec.name << " "<<"|"<<" "<<left<<setw(8)<< rec.stnum
	 << " "<<"|"<<" " <<left<<setw(11)<< rec.phone << " "<<"|"<<" " <<left<<setw(19)<< rec.mail;
	return out;
}

//Record& Record::operator=(const Record& re2) //不能是非成员函数
//{
//    if(this == &re2)
//        return *this;
//    this->name = re2.name;
//    this->stnum = re2.stnum;
//    this->phone = re2.phone;
//    this->mail = re2.mail;
//    return *this;
//}



#endif

