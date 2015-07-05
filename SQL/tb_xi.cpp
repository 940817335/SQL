#include "tb_xi.h"
#include "tb_student.h"
#include "tb_teacher.h"

bool xi::read()
{
	xi temXi;
	fstream fp("Course\\tb_xi.txt",ios::in|ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		fp.getline(temXi.xi_num,3,'\t');

		fp.getline(temXi.xi_name,15,'\t');
		fp.getline(temXi.xi_phone,9,'\t');
		fp.getline(temXi.xi_teach,5);
		vecXi.push_back(temXi);
	}
	fp.close();
	return false;
}

char* xi::getXi_name(char* xi_num)
{
	if(vecXi.size()==0)
		read();
	vector<xi>::iterator it;
	for(it=vecXi.begin();it!=vecXi.end();it++)
		if(!strcmp(it->xi_num,xi_num))
			return it->xi_name;
	return "没查到系名！";
}

bool xi::changeXi_No(char* source,char* dest){
	xi temXi;
	bool flag=false;
	char str[100];
	fstream fp("Course\\tb_xi.txt",ios::in | ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		int pos1=fp.tellg();
		fp.getline(temXi.xi_num,3,'\t');
		int pos2= fp.tellg();
		if(!strcmp(source,temXi.xi_num)){
			 fp.seekg(pos1);
			 fp << dest;   //写回去
			 fp.seekg(pos2);
			 flag=true;
		}
		fp.getline(temXi.xi_name,15,'\t');
		fp.getline(temXi.xi_phone,9,'\t');
		fp.getline(temXi.xi_teach,5);
	}
	fp.close();
	tb_student tem_stu;
	tem_stu.changeXi_Num(source,dest);
	tb_teacher tem_teach;
	tem_teach.changeXi_Num(source,dest);
	return flag;
}

bool xi::deleteXi(char* xi_num,bool isDelete,char* defVal){
	if(vecXi.size()==0)
		read();
	tb_student tem_stu;
	tb_teacher tem_teach;
	if(!isDelete){
		tem_stu.changeXi_Num(xi_num,defVal);
		tem_teach.changeXi_Num(xi_num,defVal);
	}else{
		;
	}
	vector<xi>::iterator iterXi;
	fstream fp("Course\\tb_xi.txt",ios::out|ios::trunc);
	fp << str;
	for(iterXi=vecXi.begin();iterXi!=vecXi.end()&&strcmp(iterXi->xi_num,xi_num);iterXi++){
		fp << endl << iterXi->xi_num << '\t' << iterXi->xi_name << '\t' << iterXi->xi_phone << '\t' << iterXi->xi_teach;
	}
	fp.close();
	return true;
}
