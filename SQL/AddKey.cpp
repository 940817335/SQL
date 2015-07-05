#include "AddKey.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

AddKey::AddKey(void)
{
	init();
}


AddKey::~AddKey(void)
{
}

void AddKey::init(void)
{
	char* str=new char[50];
	fstream fp("Course\\pk_records.txt",ios::in);
//	fp.seekg(0, ios::end);      //设置文件指针到文件流的尾部
    int ps = fp.tellg();  //读取文件指针的位置
	if(ps==-1){
		fp.close();
		fp.open("Course\\pk_records.txt",ios::out);
		fp << "表\t总数量\t码值";
	}
	else{
		fp.getline(str,50);
		while(!fp.eof()){
			keyRecords t;
			fp.getline(t.table,20,'\t');
			fp >> t.num;
			fp.getline(t.keyword,10);
			vecKeyInfo.push_back(t);
		}
	}
	fp.close();
	fstream fp1("Course\\fk_records.txt",ios::in);
	ps = fp1.tellg();  //读取文件指针的位置
	if(ps==-1){
		fp1.close();
		fp1.open("Course\\fk_records.txt",ios::out);
		fp1 << "表1\t列\t表2\t列";
	}
	else{
		char temp[20];
		fp1.getline(str,50);
		while(!fp1.eof()){
			FKRecords s;
			fp1.getline(temp,20,'\t');
			s.table1=temp;
			fp1.getline(temp,20,'\t');
			s.num1=atoi(temp);
			fp1.getline(temp,20,'\t');
			s.table2=temp;
			fp1.getline(temp,20,'\t');
			s.num2=atoi(temp);
			vecFK.push_back(s);
		}
	}
	fp1.close();
}

// arg0,选表;agr1,字段数量;arg2,码值
bool AddKey::addPK(int tNum, int tCount)
{
	set<string> setKeyVal;
	string tem,Tkey,table;
	char temp[100];
	fstream fp;
	int total=0,i;
	cout << "选择表：1.学生表\n2.学生成绩表\n";
	cin >> tNum;
	if(tNum==1){
		fp.open("Course\\tb_student.txt",ios::in|ios::out);
		table="tb_student.txt";
		tCount=6;
	}else{
		fp.open("Course\\tb_stuscore.txt",ios::in|ios::out);
		table="tb_stuscore.txt";
		tCount=3;
	}
	bool flag=false;
	fp.getline(temp,100);
	cout << temp << "选择字段";
	cin >> Tkey;
	while(!fp.eof()){
		string keyVal;
		for(int i=0;i<tCount;i++){
			if(i!=tCount-1)
				fp.getline(temp,20,'\t');
			else
				fp.getline(temp,20);
			if(Tkey[i]=='1'){
				if(!strcmp(temp,"")){
					flag=true;
					break;
				}
				keyVal+=temp;
			}
		}
		if(flag)
			break;
		total++;
		setKeyVal.insert(keyVal);
	}
	fp.close();
	if(flag)
		return false;
	for(i=0;i<vecKeyInfo.size();i++)
		if(table==vecKeyInfo[i].table){
			cout << "该表主键已定义";
			return false;
		}
	fp.open("Course\\pk_records.txt",ios::out|ios::app);
	fp << endl << table << "\t" << tCount << "\t" << Tkey;
	fp.close();
	return total==setKeyVal.size();
}

bool AddKey::delKey(void)
{
	int i=0,flag;
	vecKeyInfo.clear();
	init();
	for(i=0;i<vecKeyInfo.size();i++)
		cout << i+1 << "." << vecKeyInfo[i].table << "\t" << vecKeyInfo[i].num << "\t" << vecKeyInfo[i].keyword << endl;
	cout << "请输入：";
	cin >> flag;
	if(flag>i)
		return false;
	fstream fp("Course\\pk_records.txt",ios::out|ios::trunc);
	fp << "表\t总数量\t码值";
	for(i=0;i<vecKeyInfo.size();i++){
		if(i==flag-1)
			continue;
		fp << endl << vecKeyInfo[i].table << "\t" << vecKeyInfo[i].num << "\t" << vecKeyInfo[i].keyword;
	}
	fp.close();
	return true;
}

//价差插入的数据是否符合要求
bool AddKey::check(int n,string table,vector<string> agr)
{
	int i,j;
	string temp;
	char str[100];
	bool flag=false;
	for(i=0;i<vecKeyInfo.size();i++)
		if(table==vecKeyInfo[i].table){
			break;
		}
	if(i==vecKeyInfo.size())
		return true;
	string keyword=vecKeyInfo[i].keyword;
	for(j=0;j<n;j++)
		if(keyword[j+1]=='1')
			temp+=agr[j];
	fstream fp("Course\\"+table,ios::in|ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		string keyVal;
		for(i=0;i<n;i++){
			if(i!=n-1)
				fp.getline(str,20,'\t');
			else
				fp.getline(str,20);
			if(keyword[i+1]=='1')
				keyVal+=str;
		}
		if(keyVal==temp)
			return false;
	}
	return true;
}

bool AddKey::addFK(void)
{
	int i,num1,num2;
	string table1,table2;
	char temp[100];
	cout << "主表";
	cin >> table1;
	fstream fp("Course\\"+table1,ios::in);
	fp.getline(temp,100);
	fp.close();
	cout << "该表字段有：\n" << temp << "\n请选择要参考的字段";
	cin >> num1;
	for(i=0;i<vecKeyInfo.size();i++)
		cout << i+1 << "." << vecKeyInfo[i].table << "\t" << vecKeyInfo[i].num << "\t" << vecKeyInfo[i].keyword << endl;
	cout << "选表：";
	cin >> i;
	table2=vecKeyInfo[i-1].table;
	fp.open("Course\\"+table2,ios::in);
	fp.getline(temp,100);
	fp.close();
	cout << "被参考字段:" << temp << "\n请选择";;
	cin >> num2;
	if(vecKeyInfo[i-1].keyword[num2]!='1'){
		cout << "被参照字段不合适，添加外键失败";
		return false;
	}
	if(!checkFK(table1,num1,table2,num2)){
		cout << "提供的字段数据不符合规则，添加外键失败";
		return false;
	}
	fp.open("Course\\fk_records.txt",ios::in|ios::app);
	fp << endl << table1 << "\t" << num1 << "\t" << table2 << "\t" << num2;
	fp.close();
	cout << "添加主键成功";
	return true;
}

//检查数据是否符合做外键
bool AddKey::checkFK(string t1, int num1, string table2, int num2)
{
	char temp[100];
	fstream fp;
	vector<string> vecIM;
	fp.open("Course\\"+table2,ios::in);
	fp.getline(temp,100);
	while(!fp.eof()){
		for(int i=0;i<6;i++){
			if(i!=5)
				fp.getline(temp,20,'\t');
			else
				fp.getline(temp,20);
			if(i==num2-1){
				vecIM.push_back(string(temp));
			}
		}
	}
	fp.close();
	fp.open("Course\\"+t1,ios::in);
	fp.getline(temp,100);
	vector<string>::iterator iterIM;
	while(!fp.eof()){
		for(int i=0;i<3;i++){
			if(i!=2)
				fp.getline(temp,20,'\t');
			else
				fp.getline(temp,20);
			if(i==num1-1){
				bool flag=false;
				for(iterIM=vecIM.begin();iterIM!=vecIM.end();iterIM++)
					if(*iterIM==string(temp)){
						flag=true;
						break;
					}
				if(!flag){
					fp.close();
					return false;
				}
			}
		}
	}
	fp.close();
	return true;
}