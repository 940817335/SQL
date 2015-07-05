#include<iostream>
using namespace std;
#pragma once
class CoTreeNode{
public:
	CoTreeNode * left;
	CoTreeNode * next;
	char* value;
	unsigned short h;
	CoTreeNode()
	{
		left=NULL;
		next=NULL;
		value=new char(5);
	}
};