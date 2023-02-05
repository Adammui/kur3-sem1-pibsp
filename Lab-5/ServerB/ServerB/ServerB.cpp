// ServerB.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


SOCKET  serverSocket;
WSADATA wsaData;


bool GetRequestFromClient(char* name, short port, sockaddr* from, int* flen)
{
	
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		throw SetErrorMsgText("startup: ", WSAGetLastError());
	if ((serverSocket = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw  SetErrorMsgText("socket:", WSAGetLastError());
	cout << "Server start listening..." << endl;
	SOCKADDR_IN sockaddr_in;
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(port);
	sockaddr_in.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (LPSOCKADDR)&sockaddr_in, sizeof(sockaddr_in)) == SOCKET_ERROR)
		throw  SetErrorMsgText("bind:", WSAGetLastError());

	char msg[50];
	while (strcmp(msg, name) != 0)
	{
		if (recvfrom(serverSocket, msg, strlen(msg) + 1, NULL, from, flen) == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAETIMEDOUT)
				return false;
			throw SetErrorMsgText("Recvfrom: ", WSAGetLastError());
		}
	}
	return true;
}

bool PutAnswerToClient(char* name, sockaddr* to, int* lto)
{
	if (sendto(serverSocket, name, strlen(name) + 1, NULL, to, *lto) == SOCKET_ERROR)
		throw SetErrorMsgText("Sendto: ", WSAGetLastError());
	return true;
}



int main()
{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("startup: ", WSAGetLastError());
		if ((serverSocket = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw  SetErrorMsgText("socket:", WSAGetLastError());

		char* serverName = new char[50];
		if (gethostname(serverName, strlen(serverName) + 1) == SOCKET_ERROR)
			throw SetErrorMsgText("GetHostName: ", WSAGetLastError());
		std::cout << "Current server name(get host name) is " << serverName << std::endl;

		int port = 2000;
		SOCKADDR_IN from;
		int size = sizeof(from);

		while (true)
		{
			SOCKADDR_IN clientSockAddr;
			memset(&clientSockAddr, 0, sizeof clientSockAddr);
			int lenClientSockAddr = sizeof clientSockAddr;
			if (GetRequestFromClient("Hello", 2000, reinterpret_cast<sockaddr*>(&clientSockAddr), &lenClientSockAddr))
			{
				DWORD addres = inet_addr(inet_ntoa(clientSockAddr.sin_addr));
				char* clientAddress = inet_ntoa(clientSockAddr.sin_addr);
				const u_short clientPort = htons(clientSockAddr.sin_port);
				hostent* client = gethostbyaddr(reinterpret_cast<char*>(&addres), 4, AF_INET);//
				std::cout << "Client " << clientAddress << ":" << clientPort << "("
					<< client->h_name << ") sent right answer" << std::endl;
				PutAnswerToClient("Hello", reinterpret_cast<sockaddr*>(&clientSockAddr), &lenClientSockAddr);
			}
			cout << endl;
			if (closesocket(serverSocket) == SOCKET_ERROR)
				throw SetErrorMsgText("CloseSocket: ", WSAGetLastError());
			if (WSACleanup() == SOCKET_ERROR)
				throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
		}
    return 0;
}

