#pragma once
#include <vector>
using namespace std;
class keyRecords{
public:
	char table[20];
	unsigned short num;
	char keyword[10];
};

class FKRecords{
public:
	string table1;
	unsigned short num1;
	string table2;
	unsigned short num2;
};

class AddKey
{
public:
	AddKey(void);
	~AddKey(void);
	void init(void);
	vector<keyRecords> vecKeyInfo;
	vector<FKRecords> vecFK;
	// arg0,选表;agr1,字段数量;arg2,码值
	bool addPK(int tNum, int tCount);
	bool delKey(void);
	bool check(int n,string table,vector<string> arg);
	bool addFK(void);
	bool checkFK(string t1, int num1, string table2, int num2);
};