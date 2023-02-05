// lab-3serverU.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
int main()
{
    SOCKET sS; // дескриптор сокета
    WSADATA wsaData;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw SetErrorMsgText("Startup:", WSAGetLastError());
        if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
            throw SetErrorMsgText("socket:", WSAGetLastError());

        SOCKADDR_IN serv; // параметры сокета sS
        serv.sin_family = AF_INET; // используется IP-адресация
        serv.sin_port = htons(2000); // порт 2000
        serv.sin_addr.s_addr = INADDR_ANY; // адрес сервера

        if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
            throw SetErrorMsgText("bind:", WSAGetLastError());

        SOCKADDR_IN clnt; // параметры сокета клиента
        memset(&clnt, 0, sizeof(clnt)); // обнулить память
        int lc = sizeof(clnt);

        char ibuf[50]; //буфер ввода
        int lb = 0; //количество принятых байт
        int lobuf = 0; //количество отправленных
        cout << lb << endl;
        int i = 0;
        while (i < 20) {
            lb = recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)&clnt, &lc);
            if (lb == SOCKET_ERROR) {
                SetErrorMsgText("recv:", WSAGetLastError());
            }
            Sleep(1000);
            cout << ibuf << endl;
            i++;
            if (strlen(ibuf) != 0) {
                if ((lobuf = sendto(sS, ibuf, strlen(ibuf) + 1, NULL, (sockaddr*)&clnt, sizeof(clnt))) == SOCKET_ERROR)
                    throw SetErrorMsgText("send:", WSAGetLastError());
                Sleep(1000);
                lb = recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)&clnt, &lc);
                if (lb == SOCKET_ERROR) {
                    SetErrorMsgText("recv:", WSAGetLastError());
                }
                Sleep(1000);
            }
        }
        //...........................................................
        if (closesocket(sS) == SOCKET_ERROR)
            throw SetErrorMsgText("closesocket:", WSAGetLastError());
        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup:", WSAGetLastError());
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
    }

    //system("pause");
    return 0;

}

