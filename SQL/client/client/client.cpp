//Client.cpp
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <Windows.h>
#include <ctime>
 
using namespace std;
 
#define  PORT 2501
#define  IP_ADDRESS "127.0.0.1"
const int BUFSIZE=128;
 

int main(int argc, char* argv[])
{
    WSADATA  Ws;
    SOCKET CientSocket;
    struct sockaddr_in ServerAddr;
    int Ret = 0;
    int AddrLen = 0;
    HANDLE hThread = NULL;
    char SendBuffer[MAX_PATH];

     //Init Windows Socket
    if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
    {
        cout<<"Init Windows Socket Failed::"<<GetLastError()<<endl;
        return -1;
    }

    //Create Socket
    CientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ( CientSocket == INVALID_SOCKET )
    {
        cout<<"Create Socket Failed::"<<GetLastError()<<endl;
        return -1;
    }
 
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    ServerAddr.sin_port = htons(PORT);
    memset(ServerAddr.sin_zero, 0x00, 8);
 
    Ret = connect(CientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));

    if ( Ret == SOCKET_ERROR )
    {
        cout<<"Connect Error::"<<GetLastError()<<endl;
        return -1;
    }
    else
   {
        cout<<"���ӳɹ�!"<<endl;
    }
	cout << "֧��ǰ3�����ܣ������ʽ������+�ո�+����\n";
	cout << "1.��ѯѧ����Ϣ����:1 200907007\n2.��ѯѡ�˸������пε�ͬѧ,��:2 200907009\n"
		<< "3.��ѯ��ʦƽ���ɼ�,��:3 T001\n\n";
	clock_t start,finish;
	bool flag=true;
	//int val;
    while ( flag )
    {
		strcpy(SendBuffer,"");
        cin.getline(SendBuffer, sizeof(SendBuffer));
		if(!strcmp(SendBuffer,""))
			continue;
		start=clock();
        Ret = send(CientSocket, SendBuffer, (int)strlen(SendBuffer), 0);
		if(SendBuffer[0]=='q')
			break;
        if ( Ret == SOCKET_ERROR )
        {
            cout<<"Send Info Error::"<<GetLastError()<<endl;
            break;
        }
		int i;
		for(i=0;i<BUFSIZE;i++)
			SendBuffer[i]='\0';
		Ret=recv(CientSocket,SendBuffer,BUFSIZE,0); 
		cout << SendBuffer ;
		finish=clock();
		cout << "��ѯʱ��Ϊ" << (double)(finish-start)/CLOCKS_PER_SEC << "��\n\n";
     }
     
    closesocket(CientSocket);
    WSACleanup();
	system("pause");
    return 0;
}