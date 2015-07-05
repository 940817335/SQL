#pragma once
#include <fstream>
#include <vector>
using namespace std;
class xi
{
public:
	char xi_num[3];
	char xi_name[15];
	char xi_phone[9];
	char xi_teach[5];
	char str[100];
	vector<xi> vecXi;
	bool read();
	char* getXi_name(char* xi_num);
	bool changeXi_No(char* source,char* dest);
	bool deleteXi(char* xi_num,bool isDelete=false,char* defVal="00");
};