#include "tb_qinshi.h"
bool tb_qinshi::read()
{
	tb_qinshi temQin;
	char str[100];
	fstream fp("Course\\tb_qin.txt",ios::in|ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		fp.getline(temQin.qin_num,4,'\t');
		fp.getline(temQin.qin_name,13,'\t');
		fp.getline(temQin.qin_phone,9,'\t');
		fp.getline(temQin.qin_area,6);
		vecQin.push_back(temQin);
	}
	fp.close();
	return false;
}

char* tb_qinshi::getQin_name(char* qin_num)
{
	if(vecQin.size()==0)
		read();
	if(strlen(qin_num)==2)
	{
		qin_num[2]=qin_num[1];
		qin_num[1]='0';
	}
	vector<tb_qinshi>::iterator it;
	for(it=vecQin.begin();it!=vecQin.end();it++)
		if(!strcmp(it->qin_num,qin_num))
			return it->qin_name;
	return "没查到寝室名！";
}