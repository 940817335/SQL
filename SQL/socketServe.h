#include <winsock.h> 
#pragma comment(lib,"ws2_32.lib") 
#pragma once
class socketServe
{
public:
	socketServe(void);
	~socketServe(void);
	void go(void);
};

DWORD WINAPI AnswerThread(LPVOID lparam);

