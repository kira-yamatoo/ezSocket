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
	SOCKADDR_IN siServerAddr;
	WORD wRet = MAKEWORD(2, 2);
	WSADATA wsaData;

	//��ʼ��socket
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

	//���lib�汾
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wHighVersion != 2))
	{
		printf("Version  Error!\n");
	}
	else
	{
		printf("Version Success!\n");
	}

	siServerAddr.sin_family = AF_INET;
	siServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	siServerAddr.sin_port = htons(6666);

	sServer = socket(AF_INET, SOCK_STREAM, 0);
	
	//����socket
	if (connect(sServer, (SOCKADDR *)&siServerAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("connect  Error!\n");
		WSACleanup();
		return 0;
	}
	else
	{
		printf("connect  Success!\n");
	}
	
	//ѭ�����ͺͽ�������
	while (true)
	{
		//��������
		printf("input data:");
		scanf("%s", cSendBuffer);
		nSendLength= send(sServer, cSendBuffer, 100, 0);
		if (nSendLength < 0)
		{
			printf("send Failed!\n");
			break;
		}
		else
		{
			printf("send Success!\n");
		}
		//��������
		nRecvLength= recv(sServer, cRecvBuffer, 100, 0);
		if (nRecvLength < 0)
		{
			printf("recv Failed!\n");
			break;
		}
		else
		{
			printf("%s\n", cRecvBuffer);
		}

	}

	//�ر�socket
	closesocket(sServer);
	WSACleanup();

	return 0;
}