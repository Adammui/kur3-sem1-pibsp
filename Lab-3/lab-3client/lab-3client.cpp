#include <iostream>
#include "Winsock2.h" // заголовок WS2_32.dll
#pragma comment(lib, "WS2_32.lib") // экспорт WS2_32.dll

using namespace std;
#pragma warning(disable : 4996)


string  GetErrorMsgText(int code)    // cформировать текст ошибки 
{
    string msgText;
    switch (code)                      // проверка кода возврата  
    {
    case WSAEINTR:          msgText = "WSAEINTR";         break;
    case WSAEACCES:         msgText = "WSAEACCES";        break;
    case WSAEFAULT:         msgText = "WSAEFAULT";        break;
    case WSAEINVAL:         msgText = "WSAEINVAL";        break;
    case WSAEMFILE:         msgText = "WSAEMFILE";        break;
    case WSAEWOULDBLOCK:         msgText = "WSAEWOULDBLOCK";        break;
    case WSAEINPROGRESS:         msgText = "WSAEINPROGRESS";        break;
    case WSAEALREADY:         msgText = "WSAEALREADY";        break;
    case WSAENOTSOCK:         msgText = "WSAENOTSOCK";        break;
    case WSAEDESTADDRREQ:         msgText = "WSAEDESTADDRREQ";        break;
    case WSAEMSGSIZE:         msgText = "WSAEMSGSIZE";        break;
    case WSAEPROTOTYPE:         msgText = "WSAEPROTOTYPE";        break;
    case WSAENOPROTOOPT:         msgText = "WSAENOPROTOOPT";        break;
    case WSAEPROTONOSUPPORT:         msgText = "WSAEPROTONOSUPPORT";        break;
    case WSAESOCKTNOSUPPORT:         msgText = "WSAESOCKTNOSUPPORT";        break;
    case WSAEOPNOTSUPP:         msgText = "WSAEOPNOTSUPP";        break;
    case WSAEPFNOSUPPORT:         msgText = "WSAEPFNOSUPPORT";        break;
    case WSAEAFNOSUPPORT:         msgText = "WSAEAFNOSUPPORT";        break;
    case WSAEADDRINUSE:         msgText = "WSAEADDRINUSE";        break;
    case WSAEADDRNOTAVAIL:         msgText = "WSAEADDRNOTAVAIL";        break;
    case WSAENETDOWN:         msgText = "WSAENETDOWN";        break;
    case WSAENETUNREACH:         msgText = "WSAENETUNREACH";        break;
    case WSAENETRESET:         msgText = "WSAENETRESET";        break;
    case WSAECONNABORTED:         msgText = "WSAECONNABORTED";        break;
    case WSAECONNRESET:         msgText = "WSAECONNRESET";        break;
    case WSAENOBUFS:         msgText = "WSAENOBUFS";        break;
    case WSAEISCONN:         msgText = "WSAEISCONN";        break;
    case WSAENOTCONN:         msgText = "WSAENOTCONN";        break;
    case WSAESHUTDOWN:         msgText = "WSAESHUTDOWN";        break;
    case WSAETIMEDOUT:         msgText = "WSAETIMEDOUT";        break;
    case WSAECONNREFUSED:         msgText = "WSAECONNREFUSED";        break;
    case WSAEHOSTDOWN:         msgText = "WSAEHOSTDOWN";        break;
    case WSAEHOSTUNREACH:         msgText = "WSAEHOSTUNREACH";        break;
    case WSAEPROCLIM:         msgText = "WSAEPROCLIM";        break;
    case WSASYSNOTREADY:         msgText = "WSASYSNOTREADY";        break;
    case WSAVERNOTSUPPORTED:         msgText = "WSAVERNOTSUPPORTED";        break;
    case WSANOTINITIALISED:         msgText = "WSANOTINITIALISED ";        break;
    case WSAEDISCON:         msgText = "WSAEDISCON";        break;
    case WSATYPE_NOT_FOUND:         msgText = "WSATYPE_NOT_FOUND";        break;
    case WSAHOST_NOT_FOUND:         msgText = "WSAHOST_NOT_FOUND";        break;
    case WSATRY_AGAIN:         msgText = "WSATRY_AGAIN";        break;
    case WSANO_RECOVERY:         msgText = "WSANO_RECOVERY";        break;
    case WSANO_DATA:         msgText = "WSANO_DATA";        break;
    case WSA_INVALID_HANDLE:         msgText = "WSA_INVALID_HANDLE";        break;
    case WSA_INVALID_PARAMETER:         msgText = "WSA_INVALID_PARAMETER";        break;
    case WSA_IO_INCOMPLETE:         msgText = "WSA_IO_INCOMPLETE";        break;
    case WSA_IO_PENDING:         msgText = "WSA_IO_PENDING";        break;
    case WSA_NOT_ENOUGH_MEMORY:         msgText = "WSA_NOT_ENOUGH_MEMORY";        break;
    case WSA_OPERATION_ABORTED:         msgText = "WSA_OPERATION_ABORTED";        break;
    case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
    default:                msgText = "***ERROR***";      break;
    };
    return msgText;
};

string SetErrorMsgText(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};
SOCKET cC;
bool GetServer(char* call, short port, sockaddr* from, int* flen)
{
    memset(from, 0, sizeof(flen));

    if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
    {
        throw  SetErrorMsgText("socket:", WSAGetLastError());
    }

    int optval = 1;			//состояние enabled
    //установить опции сокета
    if (setsockopt(cC,
        SOL_SOCKET,		//уровень д-вия режима
        SO_BROADCAST,	//режим сокета для исп-ния широковещ.адреса
        (char*)&optval, //значение режима сокета
        sizeof(int)) == SOCKET_ERROR)	//длина буфера оптвал
    {
        throw  SetErrorMsgText("opt:", WSAGetLastError());
    }

    SOCKADDR_IN all;
    all.sin_family = AF_INET;
    all.sin_port = htons(2000);
    all.sin_addr.s_addr = INADDR_BROADCAST;

    if ((sendto(cC, call, strlen(call) + 1, NULL, (sockaddr*)&all, sizeof(all))) == SOCKET_ERROR)
    {
        throw  SetErrorMsgText("sendto:", WSAGetLastError());
    }

    char nameServer[50];
    if ((recvfrom(cC, nameServer, sizeof(nameServer), NULL, from, flen)) == SOCKET_ERROR)
    {
        if (WSAGetLastError() == WSAETIMEDOUT)
        {
            return false;
        }
        else
        {
            throw  SetErrorMsgText("recv:", WSAGetLastError());
        }
    }

    SOCKADDR_IN* addr = (SOCKADDR_IN*)&from;\

    if (!strcmp(nameServer, call))
    {
        std::cout << std::endl << "Сервер найден.";

        std::cout << std::endl << "Порт сервера: " << addr->sin_port;
        std::cout << std::endl << "IP-адрес сервера: " << inet_ntoa(addr->sin_addr);
        return true;
    }
    else
    {
        std::cout << std::endl << "Сервер не найден.";
        return false;
    }

    return true;
}

int main()
{
    setlocale(LC_CTYPE, "rus");

    WSADATA wsaData;

    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
        {
            throw  SetErrorMsgText("Startup:", WSAGetLastError());
        }

        char call[] = "Hello";

        SOCKADDR_IN clnt;
        int lc = sizeof(clnt);

        GetServer(call, 2000, (sockaddr*)&clnt, &lc);

        if (closesocket(cC) == SOCKET_ERROR)
        {
            throw  SetErrorMsgText("closesocket:", WSAGetLastError());
        }
        if (WSACleanup() == SOCKET_ERROR)
        {
            throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
        }
    }
    catch (std::string errorMsgText)
    {
        std::cout << std::endl << errorMsgText;
    }

    std::cout << std::endl;
    system("pause");
    return 0;
}

