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
	//��ȡ ѧ���� ��Ӧѧ�ŵ�λ��
	int getFilePos(int stunum);
	// ��ȡָ��λ�õ�ѧ����Ϣ
	bool searchByIndex(int stunum);
	string socketShow(int stunum);
};

class index{//������ʽ����ѧ����Ϣ
public:
	int stu_num;
	int pos;
	index(){
		stu_num=0;
		pos=0;
	}
};