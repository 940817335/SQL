#include "main.h"

int main()
{
	while(1){
		system("cls");
		char item;
		cout << "…………欢迎使用MiniSQL…………\n" << 
			"1.根据学号查学生信息\n2.查询选修了与某同学全部课程的同学\n" << 
			"3.查询教师全部课程的平均成绩\n4.统计每门课的成绩信息\n" <<
			"5.查询寝室平均成绩，从高到低排列\n6.查询超过平均分的课程号\n" <<
			"7.输出不符合选课规定的学生\n8.插入学生成绩\n9.修改系编号\n" <<
			"a.删除系\nb.主外键\nc.服务端\n其他键退出……\n请输入：";
		cin >> item;
		switch(item)
		{
		case '1':
			{
				tb_student stu;
				cout << "1.不使用索引\n使用索引\n请输入_";
				char iter;
				cin >> iter;
				cout << "请输入学号：";
				int n;
				cin >> n;
				start=clock();
				if(iter=='1'){
					stu.read();
					if(!stu.searchByNum(n))
						cout << "没找到该学生信息！";
				}else
					stu.searchByIndex(n);
				finish=clock();
				cout << "查询时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
			}
			break;
		case '2':
			{
				tb_StuScor d;
				cout << "请输入学号：";
				int n;
				cin >> n;
				start=clock();
				d.read();
				if(d.getStudentAllCourse(n)==0)
					cout << "没找到相关信息！";
				finish=clock();
				cout << "查询时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
			}
			break;
		case '3':
			{
				tb_teaccourse h;
				char te_num[5];
				cout << "请输入教师编号：";
				cin >> te_num;
				start=clock();
				h.read();
				if(h.getTeacCouAverage(te_num)=="该教师没未上课")
					cout << "该教师没上课！";
				finish=clock();
				cout << "查询时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
			}
			break;
		case '4':
			{
				tb_StuScor d;
				start=clock();
				d.getCourseInfo();
				finish=clock();
				cout << "查询时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
			}
			break;
		case '5':
			{
				tb_StuScor d;
				start=clock();
				d.showStuCourseAver(d.getStuCourseAverage());
				finish=clock();
				cout << "查询时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
			}
			break;
		case '6':
			{
				tb_StuScor d;
				start=clock();
				d.showOverAve(d.getStuCourseAverage());
				finish=clock();
				cout << "查询时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
			}
			break;
		case '7':
			{
				tb_StuScor s;
				start=clock();
				s.getIllegeStu();
				finish=clock();
				cout << "查询时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
			}
			break;
		case '8':{
			tb_StuScor t;
			char name[7],coName[21];
			int score=0;
			cout << "姓名:";
			cin >> name;
			cout << "课程:";
			cin >> coName;
			cout << "分数：";
			cin >> score;
			tb_StuScor s;
			start=clock();
			t.insertScore(name,coName,score);
			finish=clock();
			cout << "插入时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
		}
		case 'a':{
			system("cls");
			cout << "系编号："<< endl;
			char xi[3];
			cin >> xi;
			deleXi(xi);
			break;
				 }
		case '9':{
			system("cls");
			cout << "依次输入要修改的编号、修改后的编号"<< endl;
			char source[3],dest[3];
			cin >> source >> dest;
			changeXi_Num(source,dest);
			break;
				 }
		case 'b':{
			key();
			break;
				 }
		case 'c':{
			socketServe t;
			t.go();
			break;
				 }
		default:exit(0);
		}
		system("pause");
	}
	system("pause");
	return 0;
}

void changeXi_Num(char* source,char* dest){
	system("cls");
	char temp;
	cout << "1.不能更改\n2.只改系表编号(未写代码)\n3.全部表格的系编号一起改\n其他键返回……";
	cin >> temp;
	switch(temp){
	case '1':return;
	case '2':return;
	case '3':{
		xi t;
		start=clock();
		t.changeXi_No(source,dest);
		finish=clock();
		cout << "修改时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
		break;
			 }
	default:return;
	}
}

void deleXi(char* xi_num){
	system("cls");
	char temp;
	cout << "1.不能删除\n2.删除系，相关数据改为默认值\n3.删除全部相关数据\n其他键返回……";
	cin >> temp;
	xi t;
	switch(temp){
	case '1':return;
	case '2':{
		start=clock();
		t.deleteXi(xi_num,false);
		finish=clock();
		cout << "删除时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
		break;
			 }
	case '3':{
		start=clock();
		t.deleteXi(xi_num,true);
		finish=clock();
		cout << "删除时间为" << (double)(finish-start)/CLOCKS_PER_SEC << "秒\n";
		break;
			 }
	default:return;
	}
}

void key(){
	system("cls");
	AddKey t;
	cout << "1.添加主键\n2.删除主键\n3.一个测试用例：插入学生表前的检测过程"
		<< "\n4.添加外键\n其他返回";
	char item;
	cin >> item;
	switch(item){
	case '1':{
		if(t.addPK(1,6))
		cout << "添加主键成功！";
	else
		cout << "添加主键失败！";
		break;
			 }
	case '2':{
		if(t.delKey())
			cout << "删除成功";
		else
			cout << "删除失败";
		break;
			 }
	case '3':{
		cout <<  "插入信息如下：201007007	刘玥	女	07	13874996165	" << endl;
		vector<string> arg;
		arg.push_back("200907007");
		arg.push_back("刘玥");
		arg.push_back("女");
		arg.push_back("07");
		arg.push_back("13874996165");
		if(t.check(6,"tb_student.txt",arg))
			cout << "可以插入";
		else
			cout << "不可以插入";
		break;
			 }
	case '4':{
		t.addFK();
		break;
			 }
	default:return;
	}
}