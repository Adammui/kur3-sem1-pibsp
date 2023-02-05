// ClientS.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

SOCKET  clientSocket;
WSADATA wsaData;

bool GetServerByName(char* name, char* call, sockaddr* from, int* flen)
{
	hostent *host = gethostbyname(name);

	std::cout << "Symbol name of server(get host by name): " <<host<< endl;
	char msg[50];
	if (host != nullptr)
	{
		int optval = 1;
		if (setsockopt(clientSocket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char*>(&optval), sizeof(int)))
			throw SetErrorMsgText("Setsockopt: ", WSAGetLastError());

		SOCKADDR_IN all;
		all.sin_family = AF_INET;
		all.sin_port = htons(2000);
		all.sin_addr.s_addr = inet_addr(inet_ntoa(*reinterpret_cast<struct in_addr*>(host->h_addr_list[0])));

		if (sendto(clientSocket, call, strlen(call) + 1, NULL, reinterpret_cast<sockaddr*>(&all), sizeof all) == SOCKET_ERROR)
			throw SetErrorMsgText("Sendto: ", WSAGetLastError());
		else
			std::cout << "Send to server "<< call << endl;
		if (recvfrom(clientSocket, msg, sizeof msg, NULL, from, flen) == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAETIMEDOUT)
				return false;
			throw SetErrorMsgText("Recv: ", WSAGetLastError());
		}
		else 
			std::cout << "Rerv from server " << msg;
	}
	if (call == msg) return true;
	else return false;
}

int main()
{
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		throw SetErrorMsgText("Startup:", WSAGetLastError());
	if ((clientSocket = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw SetErrorMsgText("socket:", WSAGetLastError());

	SOCKADDR_IN clientSockAddr;
	memset(&clientSockAddr, 0, sizeof clientSockAddr);
	int lenClientSockAddr = sizeof clientSockAddr;
	char* serverName = "localhost";

	GetServerByName(serverName, "Hello", reinterpret_cast<sockaddr*>(&clientSockAddr), &lenClientSockAddr);

	if (closesocket(clientSocket) == SOCKET_ERROR)
		throw SetErrorMsgText("CloseSocket: ", WSAGetLastError());
	if (WSACleanup() == SOCKET_ERROR)
		throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
    return 0;
}

