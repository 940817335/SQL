#include <vector>
#include "tb_xi.h"
#include "tb_qinshi.h"
using namespace std;
#pragma once
class tb_student
{
public:
	int stu_num;
	char stu_name[7];
	char stu_sex[3];
	char xi_num[3];
	char stu_phone[12];
	char stu_qin[4];
	vector<tb_student> stu;
	void show_student();
	bool searchByNum(int argNum);
	char* getQin_num(int argNum);
	char* showNameByNum(int argNum);
	int getStuNOByName(char * strName);
	bool changeXi_Num(char* source,char* dest);
	void read();
	bool deleByXi_Num(char* xi_num);
	//获取 学生表 对应学号的位置
	int getFilePos(int stunum);
	// 获取指定位置的学生信息
	bool searchByIndex(int stunum);
	string socketShow(int stunum);
};

class index{//索引方式查找学生信息
public:
	int stu_num;
	int pos;
	index(){
		stu_num=0;
		pos=0;
	}
};