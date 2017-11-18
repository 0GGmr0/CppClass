
#ifndef RECORD_H
#define RECORD_H
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

//ͨѶ¼��������ѧ�ţ� �绰�� �ʼ�
class Record
{
public:
	friend class AddBook;
	friend ofstream& operator << (ofstream& fileout, const Record& rec);  //�����ļ�д��
	friend ifstream& operator >> (ifstream& filein, Record& rec);  //�����ļ���ȡ
	friend istream& operator >> (istream& in, Record& rec);  //��������������
	friend ostream& operator << (ostream& out, const Record& rec);  //�������������
	Record(const string& Name ="",const string& Stnum ="",const string& Phone= "",const string& Mail = "");  //���캯��
	Record(const Record& rec);  //�������캯��

	//Record& operator=(const Record& re2);  //���ظ�ֵ�����

private:
	string name;  //����
	string stnum; //ѧ��
	string phone; //�绰
	string mail;  //�ʼ�
};

//���캯��
Record::Record(const string& Name,const string& Stnum, const string& Phone, const string& Mail) :name(Name), stnum(Stnum), phone(Phone), mail(Mail) {}

//ת�����캯��
Record::Record(const Record& rec) :name(rec.name), stnum(rec.stnum), phone(rec.phone), mail(rec.mail) {}

ofstream& operator << (ofstream& fileout, const Record& rec)
{
    fileout <<setfill(' ')<< left<<setw(6) << rec.name << " "<<"|"<<" "<<left<<setw(8)<< rec.stnum
	 << " "<<"|"<<" " <<left<<setw(11)<< rec.phone << " "<<"|"<<" " <<left<<setw(19)<< rec.mail;
	return fileout;
}

//�����������������
ifstream& operator >> (ifstream& filein, Record& rec)
{
	filein >> rec.name >> rec.stnum >> rec.phone >> rec.mail;
	return filein;
}

//����������������
ostream& operator<<(ostream& out, const Record& rec)
{
	out <<setfill(' ')<< left<<setw(6) << rec.name << " "<<"|"<<" "<<left<<setw(8)<< rec.stnum
	 << " "<<"|"<<" " <<left<<setw(11)<< rec.phone << " "<<"|"<<" " <<left<<setw(19)<< rec.mail;
	return out;
}

//Record& Record::operator=(const Record& re2) //�����Ƿǳ�Ա����
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

