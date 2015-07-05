#include "CStudentApdapter.h"
StudentAdapter::StudentAdapter(int argInt)
{
	num=argInt;
}

bool StudentAdapter::operator ()(const tb_student& student)
{
	return num==student.stu_num;
}