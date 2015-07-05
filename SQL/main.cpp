#include "main.h"

int main()
{
	while(1){
		system("cls");
		char item;
		cout << "����������ӭʹ��MiniSQL��������\n" << 
			"1.����ѧ�Ų�ѧ����Ϣ\n2.��ѯѡ������ĳͬѧȫ���γ̵�ͬѧ\n" << 
			"3.��ѯ��ʦȫ���γ̵�ƽ���ɼ�\n4.ͳ��ÿ�ſεĳɼ���Ϣ\n" <<
			"5.��ѯ����ƽ���ɼ����Ӹߵ�������\n6.��ѯ����ƽ���ֵĿγ̺�\n" <<
			"7.���������ѡ�ι涨��ѧ��\n8.����ѧ���ɼ�\n9.�޸�ϵ���\n" <<
			"a.ɾ��ϵ\nb.�����\nc.�����\n�������˳�����\n�����룺";
		cin >> item;
		switch(item)
		{
		case '1':
			{
				tb_student stu;
				cout << "1.��ʹ������\nʹ������\n������_";
				char iter;
				cin >> iter;
				cout << "������ѧ�ţ�";
				int n;
				cin >> n;
				start=clock();
				if(iter=='1'){
					stu.read();
					if(!stu.searchByNum(n))
						cout << "û�ҵ���ѧ����Ϣ��";
				}else
					stu.searchByIndex(n);
				finish=clock();
				cout << "��ѯʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
			}
			break;
		case '2':
			{
				tb_StuScor d;
				cout << "������ѧ�ţ�";
				int n;
				cin >> n;
				start=clock();
				d.read();
				if(d.getStudentAllCourse(n)==0)
					cout << "û�ҵ������Ϣ��";
				finish=clock();
				cout << "��ѯʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
			}
			break;
		case '3':
			{
				tb_teaccourse h;
				char te_num[5];
				cout << "�������ʦ��ţ�";
				cin >> te_num;
				start=clock();
				h.read();
				if(h.getTeacCouAverage(te_num)=="�ý�ʦûδ�Ͽ�")
					cout << "�ý�ʦû�ϿΣ�";
				finish=clock();
				cout << "��ѯʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
			}
			break;
		case '4':
			{
				tb_StuScor d;
				start=clock();
				d.getCourseInfo();
				finish=clock();
				cout << "��ѯʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
			}
			break;
		case '5':
			{
				tb_StuScor d;
				start=clock();
				d.showStuCourseAver(d.getStuCourseAverage());
				finish=clock();
				cout << "��ѯʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
			}
			break;
		case '6':
			{
				tb_StuScor d;
				start=clock();
				d.showOverAve(d.getStuCourseAverage());
				finish=clock();
				cout << "��ѯʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
			}
			break;
		case '7':
			{
				tb_StuScor s;
				start=clock();
				s.getIllegeStu();
				finish=clock();
				cout << "��ѯʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
			}
			break;
		case '8':{
			tb_StuScor t;
			char name[7],coName[21];
			int score=0;
			cout << "����:";
			cin >> name;
			cout << "�γ�:";
			cin >> coName;
			cout << "������";
			cin >> score;
			tb_StuScor s;
			start=clock();
			t.insertScore(name,coName,score);
			finish=clock();
			cout << "����ʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
		}
		case 'a':{
			system("cls");
			cout << "ϵ��ţ�"<< endl;
			char xi[3];
			cin >> xi;
			deleXi(xi);
			break;
				 }
		case '9':{
			system("cls");
			cout << "��������Ҫ�޸ĵı�š��޸ĺ�ı��"<< endl;
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
	cout << "1.���ܸ���\n2.ֻ��ϵ����(δд����)\n3.ȫ������ϵ���һ���\n���������ء���";
	cin >> temp;
	switch(temp){
	case '1':return;
	case '2':return;
	case '3':{
		xi t;
		start=clock();
		t.changeXi_No(source,dest);
		finish=clock();
		cout << "�޸�ʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
		break;
			 }
	default:return;
	}
}

void deleXi(char* xi_num){
	system("cls");
	char temp;
	cout << "1.����ɾ��\n2.ɾ��ϵ��������ݸ�ΪĬ��ֵ\n3.ɾ��ȫ���������\n���������ء���";
	cin >> temp;
	xi t;
	switch(temp){
	case '1':return;
	case '2':{
		start=clock();
		t.deleteXi(xi_num,false);
		finish=clock();
		cout << "ɾ��ʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
		break;
			 }
	case '3':{
		start=clock();
		t.deleteXi(xi_num,true);
		finish=clock();
		cout << "ɾ��ʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n";
		break;
			 }
	default:return;
	}
}

void key(){
	system("cls");
	AddKey t;
	cout << "1.�������\n2.ɾ������\n3.һ����������������ѧ����ǰ�ļ�����"
		<< "\n4.������\n��������";
	char item;
	cin >> item;
	switch(item){
	case '1':{
		if(t.addPK(1,6))
		cout << "��������ɹ���";
	else
		cout << "�������ʧ�ܣ�";
		break;
			 }
	case '2':{
		if(t.delKey())
			cout << "ɾ���ɹ�";
		else
			cout << "ɾ��ʧ��";
		break;
			 }
	case '3':{
		cout <<  "������Ϣ���£�201007007	���h	Ů	07	13874996165	" << endl;
		vector<string> arg;
		arg.push_back("200907007");
		arg.push_back("���h");
		arg.push_back("Ů");
		arg.push_back("07");
		arg.push_back("13874996165");
		if(t.check(6,"tb_student.txt",arg))
			cout << "���Բ���";
		else
			cout << "�����Բ���";
		break;
			 }
	case '4':{
		t.addFK();
		break;
			 }
	default:return;
	}
}