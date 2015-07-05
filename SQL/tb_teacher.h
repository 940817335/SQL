#pragma once
#include <vector>
using namespace std;
class tb_teacher
{
public:
	tb_teacher(void);
	~tb_teacher(void);
	bool changeXi_Num(char* source, char* dest);
	bool deleByXi_num(char* xi_num);
	bool read(void);
	char* te_num;
	char* te_name;
	char* te_call;
	char* te_wage;
	char* te_phone;
	char* te_xi;
	vector<tb_teacher> vecTeach;
	char* str;
};

