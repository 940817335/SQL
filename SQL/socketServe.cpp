#include "socketServe.h"
#include "tb_student.h"
#include "tb_StuScor.h"
#include "tb_teaccourse.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#define BUFSIZE 1000

socketServe::socketServe(void)
{
}


socketServe::~socketServe(void)
{
}


DWORD WINAPI AnswerThread(LPVOID lparam)
{
	SOCKET ClientSocket=(SOCKET)(LPVOID)lparam; 

	int bytesRecv; 
	char* sendbuf=new char[BUFSIZE]; 
	char recvbuf[BUFSIZE]="";
	while(true) 
	{ 
		bytesRecv=SOCKET_ERROR; 
		ZeroMemory(recvbuf,BUFSIZE);
		while(bytesRecv==SOCKET_ERROR) 
		{ //Receiving Data
			bytesRecv=recv(ClientSocket,recvbuf,BUFSIZE,0); 
		}
		int i=2;
		char agr[10];
		while(recvbuf[i]!=0){
			agr[i-2]=recvbuf[i];
			i++;
		}
		agr[i-2]='\0';
		switch(recvbuf[0]){
		case '1':{
			tb_student t;
			t.read();
			strcpy(sendbuf,t.socketShow(atoi(agr)).data());
			break;
				 }
		case '2':{
			tb_StuScor t;
			t.read();
			sendbuf=t.sockShowAll(atoi(agr));
			break;
				 }
		case '3':{
			tb_teaccourse t;
			t.read();
			strcpy(sendbuf,t.getTeacCouAverage(agr).data());
			break;
				 }
		case 'q':closesocket(ClientSocket);
			return 0;
		default:continue;
		}
		send(ClientSocket,sendbuf,strlen(sendbuf),0); 
	} 
	return 0;
}


void socketServe::go(void)
{
	WSADATA wsaData; 
	int iRet=WSAStartup(MAKEWORD(2,2),&wsaData); 
	if(iRet!=NO_ERROR) 
		printf("Error at WSAStartup()\n"); 

	//create a socket 
	SOCKET m_socket; 
	m_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
	if(m_socket==INVALID_SOCKET) 
	{ 
		printf("Error at socket():%ld\n",WSAGetLastError()); 
		WSACleanup(); 
		return ; 
	} 

	//bind a socket 
	sockaddr_in service; 
	service.sin_family=AF_INET; 
	service.sin_addr.s_addr=inet_addr("127.0.0.1"); 
	service.sin_port=htons(2501); 

	if(bind(m_socket,(SOCKADDR*)&service,sizeof(service))==SOCKET_ERROR) 
	{ 
		printf("bind() failed.\n"); 
		closesocket(m_socket); 
		return ; 
	} 
	else 
		printf("bind OK.\n"); 

	//listen on a socket 
	if(listen(m_socket,20)==SOCKET_ERROR) 
		printf("Error listening on socket.\n"); 
	else 
		printf("listening ok.\n"); 

	//accept a connection 
	SOCKET AcceptSocket; 

	printf("Waiting for a client to connect...\n"); 
	while(1) 
	{ 
		AcceptSocket=SOCKET_ERROR; 
		while(AcceptSocket==SOCKET_ERROR) 
		{ 
			AcceptSocket=accept(m_socket,NULL,NULL); 
		} 
		printf("Client Connected.\n"); 

		DWORD dwThreadId; 
		HANDLE hThread; 

		hThread=CreateThread(NULL,NULL,AnswerThread,(LPVOID)AcceptSocket,0,&dwThreadId);
		
	} 
}
