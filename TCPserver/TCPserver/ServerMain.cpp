#include <stdio.h>
#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	char cSendBuffer[100];
	char cRecvBuffer[100];
	int nSendLength = 0;
	int nRecvLength = 0;
	int nLength = 0;
	SOCKET sServer;
	SOCKET sAccept;
	SOCKADDR_IN siServerAddr;
	SOCKADDR_IN siAcceptAddr;
	WORD wRet = MAKEWORD(2, 2);
	WSADATA wsaData;

	//初始化socket
	int nErrorCode;
	nErrorCode = WSAStartup(wRet, &wsaData);
	if (nErrorCode != 0)
	{
		printf("Init Sock failed!\n");
	}
	else
	{
		printf("Init Sock Success!\n");
	}

	//检查lib版本
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wHighVersion != 2))
	{
		printf("Version  Error!\n");
	}
	else
	{
		printf("Version Success!\n");
	}
	siServerAddr.sin_family = AF_INET;
	siServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	siServerAddr.sin_port = htons(6666);

	sServer = socket(AF_INET, SOCK_STREAM, 0);

	//绑定socket
	if (bind(sServer, (SOCKADDR *)&siServerAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("bind Error!\n");
		WSACleanup();
	}
	else
	{
		printf("bind Success!\n");
	}
	
	//监听socket
	if (listen(sServer, SOMAXCONN) < 0)
	{
		printf("listen Error!\n");
		WSACleanup();
	}
	else
	{
		printf("listen Success!\n");
	}
	//printf("wait for client data");

	nLength = sizeof(SOCKADDR);
	sAccept = accept(sServer, (SOCKADDR*)&siAcceptAddr, &nLength);
	if (sAccept == SOCKET_ERROR)
	{
		printf("sAccept failed!\n");
		WSACleanup();
		return 0;
	}
	else
	{
		printf("sAccept Success!\n");
	}

	//循环接收和发送数据
	while (true)
	{
		//接收客机发送过来的数据
		nRecvLength = recv(sAccept, cRecvBuffer, 100, 0);
		if (nRecvLength < 0)
		{
			printf("recv failed!\n");
			break;
		}
		else 
		{
			printf("%s\n", cRecvBuffer);
		}
		//输入需要发送至客机的数据
		printf("Send Client Data:\n");
		scanf("%s", cSendBuffer);
		nSendLength = send(sAccept, cSendBuffer, 100, 0);
		if (nSendLength < 0)
		{
			printf("send Failed!\n");
			break;
		}
	}
	
	//关闭socket
	closesocket(sServer);
	closesocket(sAccept);
	WSACleanup();

	return 0;
}