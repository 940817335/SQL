#include <functional>
#include<iostream>
#include<fstream>
#include <algorithm>
#include "tb_student.h"
using namespace std;
class StudentAdapter:public unary_function<tb_student,bool>
{
public:
    int num;
	char name[7];
    explicit StudentAdapter(int argInt);
    bool operator ()(const tb_student& student);
};//����ѧ����ѧ�Ų���ѧ����Ϣ