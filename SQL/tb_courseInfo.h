#include <vector>
#include <fstream>
#include <iostream>
#include "CoTreeNode.h"
#include "NodeNum.h"
using namespace std;
#pragma once

class tb_courseInfo
{
public:
	char co_ID[5];
	char co_name[21];
	unsigned short co_grade;
	char co_forID[5];
	vector<tb_courseInfo> vecCourse;
	vector<CoTreeNode> vecCoTreeRoot;
	void read();
	NodeNum getFloor(const char* strCoNum);
	char * getCoNumByName(const char * temName);
	int getTreeHigh(const CoTreeNode * root,const char * strCo,bool & flag);
	bool creTreeAtRoot(CoTreeNode * root,const char * ID,const char * forID);
};