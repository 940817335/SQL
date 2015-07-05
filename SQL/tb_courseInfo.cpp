#include "tb_courseInfo.h"
void tb_courseInfo::read()
{
	tb_courseInfo temCo;
	char temNum[10],str[100];
	fstream fp("Course\\tb_courseInfo.txt",ios::in|ios::out);
	fp.getline(str,100);
	while(!fp.eof()){
		fp.getline(temCo.co_ID,5,'\t');
		fp.getline(temCo.co_name,21,'\t');//\t 横向跳到下一制表位置 
		fp.getline(temNum,2,'\t');
		temCo.co_grade=atoi(temNum);
		fp.getline(temCo.co_forID,5);//字符串转换为整数
		vecCourse.push_back(temCo);//添加元素到向量末尾
	}
}

NodeNum tb_courseInfo::getFloor(const char* strCoNum)
{
	if(vecCourse.size()==0)
		read();
	vector<tb_courseInfo>::iterator iterCourse;
	if(vecCoTreeRoot.size()==0){
		for(iterCourse=vecCourse.begin();iterCourse!=vecCourse.end();iterCourse++)
		{
			CoTreeNode *pTemp=new CoTreeNode(),*cTemp=new CoTreeNode();
			if(strcmp(iterCourse->co_forID,""))
			{
				bool flag=false;
				vector<CoTreeNode>::iterator  iterNode;
				for(iterNode=vecCoTreeRoot.begin();iterNode!=vecCoTreeRoot.end();iterNode++)
					if(creTreeAtRoot(&*iterNode,iterCourse->co_ID,iterCourse->co_forID))
					{
						flag=true;
						break;
					}
				if(flag)
					continue;
				pTemp->h=1;
				strcpy(cTemp->value,iterCourse->co_ID);
				cTemp->h=2;
				pTemp->left=cTemp;
				strcpy(pTemp->value,iterCourse->co_forID);
				vecCoTreeRoot.push_back(*pTemp);
			}
			else
			{
				pTemp->h=1;
				strcpy(pTemp->value,iterCourse->co_ID);
				vecCoTreeRoot.push_back(*pTemp);
			}
		}
	}
	NodeNum temNodeNum;
	temNodeNum.h=-1;
	for(int i=0;i<vecCoTreeRoot.size();i++)
	{	
		bool flag=false;
		temNodeNum.h=getTreeHigh(&vecCoTreeRoot[i],strCoNum,flag);
		temNodeNum.t=i;
		if(flag)
			return temNodeNum;
	}
	return temNodeNum;
}

bool tb_courseInfo::creTreeAtRoot(CoTreeNode * root,const char * ID,const char * forID)
{
	
	if(root==NULL)
		return false;
	if(!strcmp(root->value,forID))
	{
		CoTreeNode * temp=new CoTreeNode();
		CoTreeNode * next=new CoTreeNode();
		strcpy(temp->value,ID);
		temp->h=root->h+1;
		if(root->left==NULL)
			root->left=temp;
		else
		{
			next=root->left;
			if(next->next!=NULL)
				next=next->next;
			next->next=temp;
		}
		return true;
	}
	if(strcmp(root->value,forID)&&root->left==NULL&&root->next==NULL)
		return false;
	return creTreeAtRoot(root->left,ID,forID)||creTreeAtRoot(root->next,ID,forID);
}

int tb_courseInfo::getTreeHigh(const CoTreeNode * root,const char * strCo,bool & flag)
{
	if(root==NULL)
		return -1;
	flag=false;
	if(!strcmp(root->value,strCo))
	{
		flag=true;
		return root->h;
	}
	else
	{
		int n;
		n=getTreeHigh(root->left,strCo,flag);
		if(flag)
			return n;
		n=getTreeHigh(root->next,strCo,flag);
		if(flag)
			return n;
	}
}

char * tb_courseInfo::getCoNumByName(const char * temName){
	if(vecCourse.size()==0)
		read();
	vector<tb_courseInfo>::iterator iterCourse;
	bool flag=false;
	for(iterCourse=vecCourse.begin();iterCourse!=vecCourse.end();iterCourse++)
		if(!strcmp(iterCourse->co_name,temName)){
			flag=true;
			break;
		}
	if(flag)
		return iterCourse->co_ID;
	else
		return NULL;
}