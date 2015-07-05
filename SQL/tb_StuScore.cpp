#include "tb_StuScor.h"

bool bigger(const stuCourInfo & v1,const stuCourInfo & v2)
{
	return v1.average>v2.average;
}

int tb_StuScor::getStudentAllCourse(int argNum)
{
	vector<char*> vecCourse;
	vector<tb_StuScor>::iterator iter;
    for (iter=stuScor.begin();iter!=stuScor.end();iter++)
    {
		if(iter->stu_num==argNum)
			vecCourse.push_back(iter->co_num);
    }
	unsigned short count[10000]={0};
	for (iter=stuScor.begin();iter!=stuScor.end();iter++)
	{
		vector<char*>::iterator temCourse;
		for(temCourse=vecCourse.begin();temCourse!=vecCourse.end();temCourse++)
			if(!strcmp(*temCourse,iter->co_num))
				count[iter->stu_num%200900000]++;
	}
	tb_student t;
	t.read();
	int j=0;
	for(int i=0;i<10000;i++)
		if(count[i]==vecCourse.size()&&vecCourse.size()!=0)
		{
			t.searchByNum(i+200900000);
			j++;
		}
	return j;
}

bool tb_StuScor::read()
{
	tb_StuScor temStuScor;
	char temNum[10],str[100];
	fstream fp("Course\\tb_stuscore.txt",ios::in|ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		fp.getline(temNum,10,'\t');
		temStuScor.stu_num=atoi(temNum);
		fp.getline(temStuScor.co_num,5,'\t');
		fp.getline(temNum,4);
		temStuScor.co_score=atoi(temNum);
		stuScor.push_back(temStuScor);
	}
	fp.close();
	return false;
}

float tb_StuScor::getOneAverage(char * tem_co_num)
{
	if(stuScor.size()==0)
		read();
	vector<tb_StuScor>::iterator iter;
	int total=0,count=0;
	for (iter=stuScor.begin();iter!=stuScor.end();iter++)
	{
		if(!strcmp(iter->co_num,tem_co_num))
		{
			total+=iter->co_score;
			count++;
		}
	}
	cout << tem_co_num << "平均分为：" << (float)total/count << "分\n";
	return (float)total/count;
}

bool tb_StuScor::getCourseInfo()
{
	if(stuScor.size()==0)
		read();
	vector<couseInfo> vecCourseInfo;
	vector<couseInfo>::iterator itCourseInfo;
	vector<tb_StuScor>::iterator iter;
	bool flag;
	for(iter=stuScor.begin();iter!=stuScor.end();iter++)
	{
		flag=true;
		for(itCourseInfo=vecCourseInfo.begin();itCourseInfo!=vecCourseInfo.end();itCourseInfo++)
			if(!strcmp(itCourseInfo->co_num,iter->co_num))
			{
				itCourseInfo->count++;
				itCourseInfo->total+=iter->co_score;
				if(iter->co_score<60)
					itCourseInfo->less60++;
				if(iter->co_score>itCourseInfo->max)
					itCourseInfo->max=iter->co_score;
				if(iter->co_score < itCourseInfo->min)
					itCourseInfo->min=iter->co_score;
				flag=false;
			}
		if(flag)
		{
			couseInfo temp;
			strcpy(temp.co_num,iter->co_num);
			temp.count=1;
			temp.total=iter->co_score;
			temp.less60=0;
			if(iter->co_score<60)
					temp.less60++;
			temp.max=iter->co_score;
			temp.min=iter->co_score;
			vecCourseInfo.push_back(temp);
		}
	}
	if(vecCourseInfo.size()==0)
		return false;
	cout << "课程\t平均分\t最高分\t最低分\t不及格人数\n";
	for(itCourseInfo=vecCourseInfo.begin();itCourseInfo!=vecCourseInfo.end();itCourseInfo++)
	{
		cout << itCourseInfo->co_num << "\t" << itCourseInfo->total/itCourseInfo->count << "\t" <<
			itCourseInfo->max << "\t" << itCourseInfo->min << "\t" << itCourseInfo->less60 << endl;
	}
	return true;
}

vector<stuCourInfo> tb_StuScor::getStuCourseAverage()
{
	if(stuScor.size()==0)
		read();
	vector<stuCourInfo> vecStuCourInfo;
	vector<stuCourInfo>::iterator itStuCourInfo;
	vector<tb_StuScor>::iterator iter;
	bool flag;
	tb_student t;
	for(iter=stuScor.begin();iter!=stuScor.end();iter++)
	{
		flag=true;
		for(itStuCourInfo=vecStuCourInfo.begin();itStuCourInfo!=vecStuCourInfo.end();itStuCourInfo++)
			if(iter->stu_num==itStuCourInfo->stu_num)
			{
				itStuCourInfo->count++;
				itStuCourInfo->total+=iter->co_score;
				flag=false;
			}
		if(flag)
		{
			stuCourInfo temp;
			temp.stu_num=iter->stu_num;
			temp.count=1;
			temp.total=iter->co_score;
			strcpy(temp.qin_num,t.getQin_num(temp.stu_num));
			vecStuCourInfo.push_back(temp);
		}
	}
	for(itStuCourInfo=vecStuCourInfo.begin();itStuCourInfo!=vecStuCourInfo.end();itStuCourInfo++)
		itStuCourInfo->average=(double)itStuCourInfo->total/itStuCourInfo->count;
	return vecStuCourInfo;
}

//功能5，寝室平均成绩从高到低排列
void tb_StuScor::showStuCourseAver(vector<stuCourInfo> vecStuCourInfo)
{
	cout << "学号\t课程数\t平均分\t寝室\n";
	vector<char*> vecQin_num;
	vector<char*>::iterator itQin_num;
	bool flag;
	vector<stuCourInfo>::iterator itStuCourInfo;
	for(itStuCourInfo=vecStuCourInfo.begin();itStuCourInfo!=vecStuCourInfo.end();itStuCourInfo++)
	{
		itStuCourInfo->average=(double)itStuCourInfo->total/itStuCourInfo->count;
		flag=true;
		for(itQin_num=vecQin_num.begin();itQin_num!=vecQin_num.end();itQin_num++)
			if(!strcmp(*itQin_num,itStuCourInfo->qin_num))
				flag=false;
		if(flag)
			vecQin_num.push_back(itStuCourInfo->qin_num);
	}
	for(itQin_num=vecQin_num.begin();itQin_num!=vecQin_num.end();itQin_num++)
	{
		vector<stuCourInfo> vecTemp;
		for(itStuCourInfo=vecStuCourInfo.begin();itStuCourInfo!=vecStuCourInfo.end();itStuCourInfo++)
			if(!strcmp(*itQin_num,itStuCourInfo->qin_num))
				vecTemp.push_back(*itStuCourInfo);
		sort(vecTemp.begin(),vecTemp.end(),bigger);
		for(itStuCourInfo=vecTemp.begin();itStuCourInfo!=vecTemp.end();itStuCourInfo++)
			cout << itStuCourInfo->stu_num << "\t" << itStuCourInfo->count << "\t" <<
				itStuCourInfo->average << "\t" << itStuCourInfo->qin_num << endl;
	}
}

void tb_StuScor::showOverAve(vector<stuCourInfo> vecStuCourInfo)
{
	vector<tb_StuScor>::iterator iter;
	vector<stuCourInfo>::iterator itStuCourInfo;
	for(itStuCourInfo=vecStuCourInfo.begin();itStuCourInfo!=vecStuCourInfo.end();itStuCourInfo++)
	{
		cout << itStuCourInfo->stu_num << "\t";
		for(iter=stuScor.begin();iter!=stuScor.end();iter++)
			if(iter->stu_num==itStuCourInfo->stu_num&&iter->co_score>itStuCourInfo->average)
				cout << iter->co_num << "  ";
		cout << endl;
	}
}

void tb_StuScor::getIllegeStu()
{
	if(stuScor.size()==0)
		read();
	vector<stuNodeNum> vecStuNode;
	vector<tb_StuScor>::iterator iter;
	vector<stuNodeNum>::iterator iterStuNodeNum;
	tb_courseInfo t;
	for(iter=stuScor.begin();iter!=stuScor.end();iter++){
		bool flag=false;
		for(iterStuNodeNum=vecStuNode.begin();iterStuNodeNum!=vecStuNode.end();iterStuNodeNum++)
			if(iterStuNodeNum->stuNum==iter->stu_num){
				NodeNum temNodeNum=t.getFloor(iter->co_num);
				iterStuNodeNum->vecStuNodeNum.push_back(temNodeNum);
				bool flag=true;
			}
		if(flag)
			continue;
		stuNodeNum temStuNodeNum;
		temStuNodeNum.stuNum=iter->stu_num;
		NodeNum temNodeNum=t.getFloor(iter->co_num);
		vector<NodeNum> vecStuNodeNum=temStuNodeNum.vecStuNodeNum;
		vecStuNodeNum.push_back(temNodeNum);
		vecStuNode.push_back(temStuNodeNum);
	}
	tb_student stu;
	for(iterStuNodeNum=vecStuNode.begin();iterStuNodeNum!=vecStuNode.end();iterStuNodeNum++){
		int oneCoNum=iterStuNodeNum->vecStuNodeNum.size();
		for(int i=0;i<oneCoNum&&oneCoNum!=1;i++)
			for(int j=i+1;j<oneCoNum;j++){
				if(iterStuNodeNum->vecStuNodeNum[i].h!=iterStuNodeNum->vecStuNodeNum[j].h&&
					iterStuNodeNum->vecStuNodeNum[i].t==iterStuNodeNum->vecStuNodeNum[j].t)
					stu.showNameByNum(iterStuNodeNum->stuNum);
			}
	}
	cout << endl;
}

void tb_StuScor::insertScore(char* stuName,const char * CoName,const int num){
	tb_student stu;
	tb_courseInfo coInfo;
	int stuNum=stu.getStuNOByName(stuName);
	char CoNum[21];
	strcpy(CoNum,coInfo.getCoNumByName(CoName));
	if(stuNum==-1)
		cout << "没找到此人！";
	if(CoNum==NULL)
		cout << "没有此课！";
	fstream fp("Course\\tb_stuscore.txt",ios::out|ios::app);
	fp << endl << stuNum << "\t" << CoNum << "\t" << num ;
	fp.close();
}

char* tb_StuScor::sockShowAll(int argNum)
{vector<char*> vecCourse;
	vector<tb_StuScor>::iterator iter;
    for (iter=stuScor.begin();iter!=stuScor.end();iter++)
    {
		if(iter->stu_num==argNum)
			vecCourse.push_back(iter->co_num);
    }
	unsigned short count[10000]={0};
	for (iter=stuScor.begin();iter!=stuScor.end();iter++)
	{
		vector<char*>::iterator temCourse;
		for(temCourse=vecCourse.begin();temCourse!=vecCourse.end();temCourse++)
			if(!strcmp(*temCourse,iter->co_num))
				count[iter->stu_num%200900000]++;
	}
	tb_student t;
	t.read();
	char* str=new char[1000];
	strcpy(str,"\0");
	for(int i=0;i<10000;i++){
		char* temp=new char[7];
		if(count[i]==vecCourse.size()&&vecCourse.size()!=0){
			temp=t.showNameByNum(i+200900000);
			if(temp!=NULL){
				strcat(str,temp);
				strcat(str," ");
			}
		}
	}
	if(str[0]=='\0')
		strcpy(str,"没有符合要求的数据\n");
	else
		strcat(str,"\n");
	return str;
}
