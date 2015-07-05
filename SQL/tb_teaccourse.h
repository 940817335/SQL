#include <vector>
#include <iostream>
#include "tb_StuScor.h"
#include<fstream>
using namespace std;
class tb_teaccourse
{
public:
	char te_num[5];
	char co_num[5];
	vector<tb_teaccourse> vecTeacCourse;
	string getTeacCouAverage(char* te_num);
	bool read();
};