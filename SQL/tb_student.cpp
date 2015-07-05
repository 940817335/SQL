#include "CStudentApdapter.h"
#include "tb_student.h"
#include <ctime>
#include <string>

void deleteSpace(char * str){//understood 删除读取出来行的空格
	int n=strlen(str);
	for(int i=0;i<n;i++){
		if(str[i]==' '){
			int j;
			for(j=i;j<n-1&&str[j]!='\0';j++)
				str[j]=str[j+1];
			str[j]='\0';
			i--;
		}
	}
}

void tb_student::show_student()//understood输出学生信息
{
	xi t;
	tb_qinshi qin;
	cout << stu_num << '\t' << stu_name << '\t' << stu_sex << '\t' << t.getXi_name(xi_num) << '\t' << stu_phone  << '\t' <<
		qin.getQin_name(stu_qin) << endl;
}

bool tb_student::searchByNum(int argNum)






{
	vector<tb_student>::iterator itStu;
	itStu=find_if(stu.begin(),stu.end(),StudentAdapter(argNum));
	if(itStu!=stu.end())
	{
		itStu->show_student();
		return true;
	}
	else
		return false;
}

void tb_student::read()
{
	tb_student temStu;
	char temNum[10],str[100];
	fstream fp("Course\\tb_student.txt",ios::in|ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		fp.getline(temNum,10,'\t');
		temStu.stu_num=atoi(temNum);
		fp.getline(temStu.stu_name,7,'\t');
		fp.getline(temStu.stu_sex,3,'\t');
		fp.getline(temStu.xi_num,3,'\t');
		fp.getline(temStu.stu_phone,12,'\t');
		fp.getline(temStu.stu_qin,4);
		stu.push_back(temStu);
	}
	fp.close();
}

char* tb_student::getQin_num(int argNum)
{
	if(stu.size()==0)
		read();
	vector<tb_student>::iterator itStu;
	itStu=find_if(stu.begin(),stu.end(),StudentAdapter(argNum));
	if(itStu!=stu.end())
		return itStu->stu_qin;
	else
		return "";
}

char* tb_student::showNameByNum(int argNum){
	vector<tb_student>::iterator itStu;
	if(stu.size()==0)
		read();
	itStu=find_if(stu.begin(),stu.end(),StudentAdapter(argNum));
	if(itStu!=stu.end())
	{
		cout << itStu->stu_name << "\t";
		return itStu->stu_name;
	}
	return NULL;
}

int tb_student::getStuNOByName(char * strName){
	if(stu.size()==0)
		read();
	vector<tb_student>::iterator itStu;
	for(itStu=stu.begin();itStu!=stu.end();itStu++){
		deleteSpace(strName);
		deleteSpace(itStu->stu_name);
		if(!strcmp(strName,itStu->stu_name))
			return itStu->stu_num;
	}
	return -1;
}

bool tb_student::changeXi_Num(char* source,char* dest)
{
	tb_student temStu;
	char temNum[10],str[100];
	bool flag=false;
	fstream fp("Course\\tb_student.txt",ios::in|ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		fp.getline(temNum,10,'\t');
		temStu.stu_num=atoi(temNum);
		fp.getline(temStu.stu_name,7,'\t');
		fp.getline(temStu.stu_sex,3,'\t');
		int pos1=fp.tellg();
		fp.getline(temStu.xi_num,3,'\t');
		int pos2= fp.tellg();
		if(!strcmp(source,temStu.xi_num)){
			 fp.seekg(pos1);
			 fp << dest;   //写回去
			 fp.seekg(pos2);
			 flag=true;
		}
		fp.getline(temStu.stu_phone,12,'\t');
		fp.getline(temStu.stu_qin,4);
	}
	fp.close();
	return flag;
}

bool tb_student::deleByXi_Num(char* xi_num)
{
	if(stu.size()==0)
		read();
	vector<tb_student>::iterator iterStu;
	fstream fp("Course\\tb_xi.txt",ios::out|ios::trunc);
	if(!fp)
		return false;
	fp << "学号	姓名	性别	所在系	手机号码	寝室";
	for(iterStu=stu.begin();iterStu!=stu.end()&&strcmp(xi_num,iterStu->xi_num);iterStu++)
		fp << endl << iterStu->stu_num << '\t' << iterStu->stu_name << '\t' << iterStu->stu_sex << '\t'
		<< iterStu->xi_num << '\t' << iterStu->stu_phone << '\t' << iterStu->stu_qin ;
	fp.close();
	return true;
}




// 对 学生表 添加索引文件
int tb_student::getFilePos(int stunum)
{
	fstream fp("Course\\index_stu.dat",ios::in|ios::binary);
	index t;
	if(!fp||fp.eof()){
		fp.close();
		clock_t start,finish;
		start=clock();
		fp.open("Course\\index_stu.dat",ios::out|ios::binary);
		fstream fTable("Course\\tb_student.txt",ios::in|ios::out);
		char str[100];
		fTable.getline(str,100);
		while(!fTable.eof()){
			t.pos=fTable.tellg();
			fTable >> t.stu_num;
			fp.write((char*)&t,sizeof(index));
			fTable.getline(str,100);
		}
		fTable.close();
		fp.close();
		finish=clock();
		cout << "创索引花费时间：" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
		fp.open("Course\\index_stu.dat",ios::in|ios::binary);
	}
	index ind_stu[10000];
	int i=0;
	while(!fp.eof()){
		fp.seekp(sizeof(index)*i);
		fp.read((char*)&t,sizeof(index));
		ind_stu[t.stu_num%200900000]=t;
		i++;
	}
	fp.close();
	return ind_stu[stunum%200900000].pos;
}



// 获取指定位置的学生信息
bool tb_student::searchByIndex(int stunum)
{
	tb_student temStu;
	char temNum[10];
	fstream fp("Course\\tb_student.txt",ios::in);
	int n=getFilePos(stunum);
	fp.seekg(n);
	fp.getline(temNum,10,'\t');
	temStu.stu_num=atoi(temNum);
	fp.getline(temStu.stu_name,7,'\t');
	fp.getline(temStu.stu_sex,3,'\t');
	fp.getline(temStu.xi_num,3,'\t');
	fp.getline(temStu.stu_phone,12,'\t');
	fp.getline(temStu.stu_qin,4);
	temStu.show_student();
	fp.close();
	return false;
}


string tb_student::socketShow(int stunum)
{
	vector<tb_student>::iterator itStu;
	string s;
	itStu=find_if(stu.begin(),stu.end(),StudentAdapter(stunum));
	if(itStu!=stu.end())
	{
		xi t;
		tb_qinshi qin;
		char* temp=new char[10];
		itoa(itStu->stu_num,temp,10);
		s=string(temp)+"\t"+string(itStu->stu_name)+"\t"+string(itStu->stu_sex)+"\t"+string(t.getXi_name(itStu->xi_num))+"\t"
			+string(itStu->stu_phone)+"\t"+string(qin.getQin_name(itStu->stu_qin))+"\n";
	}
	else
		s="没有找到该学生";
	return s;
}
