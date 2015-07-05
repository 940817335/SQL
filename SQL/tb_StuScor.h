#include <vector>
#include <iostream>
#include <algorithm>
#include "tb_student.h"
#include "tb_courseInfo.h"
#include<fstream>
using namespace std;

//ѧ���ɼ���Ϣͳ�ƽṹ��
#pragma once
class stuCourInfo
{
public:
	int stu_num;
	int total;
	int count;
	char qin_num[4];
	float average;
};

//ѧ��ѡ�γɼ�
#pragma once
class tb_StuScor
{
public:
	int stu_num;
	char co_num[5];
	unsigned short co_score;
	vector<tb_StuScor> stuScor;
	int getStudentAllCourse(int argNum);
	float getOneAverage(char * tem_co_num);
	bool getCourseInfo();
	bool read();
	void insertScore(char * stuName,const char * CoName,const int num=0);
	vector<stuCourInfo> getStuCourseAverage();
	void showStuCourseAver(vector<stuCourInfo> );
	void showOverAve(vector<stuCourInfo>);
	void getIllegeStu();
	char* sockShowAll(int argNum);
};

/*******************
*�γ���Ϣͳ�ƽṹ��*
*******************/
#pragma once
class couseInfo
{
public:
	char co_num[5];
	float total;
	int count;
	int max;
	int min;
	int less60;
};

#pragma once
class stuNodeNum{
public:
	int stuNum;
	vector<NodeNum> vecStuNodeNum;
};