#include "tb_teaccourse.h"
#include <string>
using namespace std;

bool tb_teaccourse::read()
{
	tb_teaccourse temTeacCour;
	char str[100];
	fstream fp("Course\\tb_teaccourse.txt",ios::in|ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		fp.getline(temTeacCour.te_num,5,'\t');
		fp.getline(temTeacCour.co_num,5);
		vecTeacCourse.push_back(temTeacCour);
	}
	fp.close();
	return false;
}

string tb_teaccourse::getTeacCouAverage(char* te_num)
{
	vector<char*> vecCourse;
	vector<tb_teaccourse>::iterator iter;
    for (iter=vecTeacCourse.begin();iter!=vecTeacCourse.end();iter++)  
    {
		if(!strcmp(iter->te_num,te_num))
			vecCourse.push_back(iter->co_num);
    }
	vector<char*>::iterator itCourse;
	string s,temp;
	char* score=new char[2];
	for (itCourse=vecCourse.begin();itCourse!=vecCourse.end();itCourse++)
	{
		tb_StuScor t;
		sprintf(score,"%f",t.getOneAverage(*itCourse));
		temp=string(*itCourse)+"\t"+string(score)+"\n";
		s+=temp;
	}
	if(vecCourse.size()==0)
		return "该教师未上课";
	return s;
}