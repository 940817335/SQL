#include "tb_teacher.h"
#include <fstream>
using namespace std;

tb_teacher::tb_teacher(void)
{
}


tb_teacher::~tb_teacher(void)
{
}


bool tb_teacher::changeXi_Num(char* source, char* dest)//�ı�ϵ����
{

	char temNum[5],str[100],name[7],call[7],wage[5],phone[12],xi_num[3];
	bool flag=false;
	fstream fp("Course\\tb_teacher.txt",ios::in|ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		fp.getline(temNum,5,'\t');
		fp.getline(name,7,'\t');
		fp.getline(call,7,'\t');
		fp.getline(wage,5,'\t');
		fp.getline(phone,12,'\t');
		int pos1=fp.tellg();//���ص�ǰָ��
		fp.getline(xi_num,3);
		int pos2= fp.tellg();
		if(!strcmp(source,xi_num)){
			 fp.seekg(pos1);
			 fp << dest;   //д��ȥ
			 fp.seekg(pos2);//����seekg()����������������������������"get"ָ�뵽��ǰ���Ĵ�originƫ��offset���ֽڵ�λ���ϣ�
			//����"get"ָ����positionλ�á�
			 flag=true;
		}
	}
	fp.close();
	return flag;
}


bool tb_teacher::deleByXi_num(char* xi_num)//ͨ��ϵ��ɾ��ϵ�������ʦ
{
	fstream fp("Course\\tb_teacher.txt",ios::out|ios::trunc);
	fp << str;
	vector<tb_teacher>::iterator iterTeach;
	for(iterTeach=vecTeach.begin();iterTeach!=vecTeach.end()&&strcmp(xi_num,iterTeach->te_xi);iterTeach++)
		fp << endl << iterTeach->te_num << '\t' << iterTeach->te_name << '\t' << iterTeach->te_call
		<< '\t' << iterTeach->te_wage << '\t' << iterTeach->te_phone << '\t' << iterTeach->te_xi;
	fp.close();
	return true;
}


bool tb_teacher::read(void)//understood ���ļ��ж����ݵ�����
{
	tb_teacher temTech;
	fstream fp("Course\\tb_teacher.txt",ios::in|ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		fp.getline(temTech.te_num,5,'\t');
		fp.getline(temTech.te_name,7,'\t');
		fp.getline(temTech.te_call,7,'\t');
		fp.getline(temTech.te_wage,5,'\t');
		fp.getline(temTech.te_phone,12,'\t');
		fp.getline(temTech.te_xi,3);
		vecTeach.push_back(temTech);
	}
	fp.close();
	return true;
}
