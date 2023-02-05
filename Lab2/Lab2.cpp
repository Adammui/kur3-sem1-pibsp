#include <iostream>

#include "Winsock2.h"                // заголовок  WS2_32.dll
#include <string>
using namespace std;
#pragma comment(lib, "WS2_32.lib")   // экспорт  WS2_32.dll

// -- инициализировать библиотеку WS2_32.DLL
// Назначение: функция  позволяет инициализировать 
//             динамическую библиотеку, проверить номер
//             версии, получить сведения о конкретной    
//             реализации библиотеки. Функция должна быть 
//             выполнена до использования любой функции
//             Windows Sockets
//
int WSAStartup(
    WORD         ver,  //[in]  версия  Windows Sockets  
    lpWSAData    wsd   //[out] указатель на WSADATA 
);
// Код возврата: в случае успешного завершения функция 
//               возвращает нулевое значение, в случае ошибки 
//               возвращается не нулевое  значение       
// Примечания: - параметр ver представляет собой два байта,
//               содержащих номер версии Windows Sockets,
//               причем.  старший байт содержит
//               младший номер версии, а младший байт- 
//               старший номер версии;
//             - обычно параметр ver задается с помощью макро //               MAKEWORD; 
//             - шаблон структуры WSADATA содержится в 
//               Winsock2.h
// -- создать сокет 
// Назначение: функция  позволяет создать сокет (точнее
//             дескриптор сокета) и задать его характеристики 
//
SOCKET socket(
    int    af,   //[in]  формат адреса  
    int    type, //[in]  тип сокета   
    int    prot  //[in]  протокол
);
// Код возврата: в случае успешного завершения функция 
//               возвращает дескриптор сокета, в другом   
//               случае возвращается INVALID_SOCKET       
// Примечания: - параметр af для стека TCP/IP принимает
//               значение AF_INET;
//             - параметр type может принимать два значения: 
//               SOCK_DGRAM – сокет, ориентированный на
//               сообщения(UDP); SOCK_STREEM – сокет 
//               ориентированный на поток;    
//               старший номер версии;
//             - параметр prot определяет  протокол 
//               транспортного уровня: для TCP/IP можно 
//               указать NULL   
// -- закрыть существующий  сокет 
// Назначение: переводит сокет в неработоспособное состояние и
//             освобождает все ресурсы связанные с ним  
//
SOCKET closesocket(
    SOCKET s,    //[in] дескриптор сокета   
    );
// Код возврата: в случае успешного завершения функция 
//               возвращает нуль, в другом случае  
//               возвращается SOCKET_ERROR       
// -- связать сокет с параметрами
// Назначение: функция связывает существующий сокет с   
//             с параметрами, находящимися в структуре  
//             SOCKADDR_IN    
//
int bind(
    SOCKET s,                    //[in] сокет
    cost struct sockaddr_in* a, //[in] указатель на SOCKADDR_IN
    int    la                    //[in] длина SOCKADDR_IN в байтах
)
// Код возврата: в случае успешного завершения функция 
//               возвращает нуль, в случае ошибки 
//               возвращается SOCKET_ERROR       


int main()
{
    SOCKET  sS;
    WSADATA wsaData;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw  SetErrorMsgText("Startup:", WSAGetLastError());

        if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
            throw  SetErrorMsgText("socket:", WSAGetLastError());
//............................................................
        if (closesocket(sS) == SOCKET_ERROR)
            throw  SetErrorMsgText("closesocket:", WSAGetLastError());

        if (WSACleanup() == SOCKET_ERROR)
            throw  SetErrorMsgText("Cleanup:", WSAGetLastError());

    }
    catch (string errorMsgText)
    {
        cout << endl << "WSAGetLastError: " << errorMsgText;
    }

    //................................................................
    return 0;
}

//обработка ошибок
string  GetErrorMsgText(int code)    // cформировать текст ошибки 
{
    string msgText;
    switch (code)                      // проверка кода возврата  
    {
    case WSAEINTR:          msgText = "WSAEINTR";         break;
    case WSAEACCES:         msgText = "WSAEACCES";        break;
        //..........коды WSAGetLastError ..........................
    case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
    default:                msgText = "***ERROR***";      break;
    };
    return msgText;
};
string  SetErrorMsgText(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};


