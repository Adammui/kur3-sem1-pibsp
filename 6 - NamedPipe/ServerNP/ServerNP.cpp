/*#include "pch.h"
#include <iostream>
#include <Winsock2.h>///его достаточно (синтаксис в KERNEL32.DLL)
#include <string>
#define PIPE TEXT("\\\\.\\pipe\\Tube")

#define MAX_SIZE_OF_BUFFER 64

int main()
{
	DWORD dwRead;
	char* buffer = new char[MAX_SIZE_OF_BUFFER];
	try
	{
		HANDLE hPipe = CreateNamedPipe(
			PIPE,
			PIPE_ACCESS_DUPLEX |
			PIPE_TYPE_BYTE |
			PIPE_READMODE_BYTE,
			PIPE_TYPE_MESSAGE |
			PIPE_READMODE_MESSAGE,
			1,						///макс кол-во экземпляров канала
			1024 * 16,				///р-р вых буфера
			1024 * 16,				///р-р вход буфера
			NMPWAIT_USE_DEFAULT_WAIT,
			NULL		
		);
		if (hPipe == INVALID_HANDLE_VALUE)
			throw "Named Pipe can't be created";


		if (!ConnectNamedPipe(hPipe, NULL))
			throw "Troubles with client connection";

		
		while (ReadFile(hPipe, buffer, strlen(buffer) - 1, &dwRead, NULL)!=FALSE)
		{
			buffer[dwRead] = '\0';
			puts(buffer);
			
			WriteFile(hPipe, buffer, strlen(buffer), &dwRead, NULL);
		}
		
		DisconnectNamedPipe(hPipe);
		CloseHandle(hPipe);
	}
	catch (char* err)
	{
		puts(err);
	}
	delete[] buffer;
	system("pause");
	return 0;
}
*/

//ИК - объект ядра ОС, обесп. обмен д-ми м/процессами, на пк в 1 лок.сети
//сервер ИК - процесс, созд. ИК
//клиент ИК - процесс, связ. с ИК

//ИК : дупл и полудупл
//обмен д-ми : синх и асинх

/* Все ф-ции:
	1) ф. упр каналом:
		* созд канал
		* соед сервер с каналом
		* откр канал
		* получ инфу об ИК
		* получ сост ИК
		* изм хар-ки ИК
	2) ф. обмена д-ми:
		* писать в ИК
		* читать из ИК
		* копир д-е ИК
	3) ф. для работы с транз


	Сервер							Клиент
 sH = CreateNamedPipe			cH = CreateFile				//уст связь с ИК
 ConnectNamedPipe
 char rbuf[..]					char wbuf[..]
								WriteFile (cH...)			//и наоборот тоже
 ReadFile(sH...)
 DisconnectNamedPipe
 CloseHandle(sH)				CloseHandle(cH)
*/


#include "pch.h"
#include <iostream>
#include <Winsock2.h>
#include <string>

#define PIPE TEXT("\\\\.\\pipe\\Tube")

#define MAX_SIZE_OF_BUFFER 64

int main()
{
	DWORD dwRead;
	char* buffer = new char[MAX_SIZE_OF_BUFFER];
	try
	{
		HANDLE hPipe = CreateNamedPipe(
			PIPE, //имя
			PIPE_ACCESS_DUPLEX |
			PIPE_TYPE_BYTE |
			PIPE_READMODE_BYTE,
			PIPE_TYPE_MESSAGE |
			PIPE_READMODE_MESSAGE,
			1,						///макс кол-во экземпляров канала
			1024 * 16,				///размер вых буфера
			1024 * 16,				///размерр вход буфера
			NMPWAIT_USE_DEFAULT_WAIT,
			NULL
		); // создать канал
		if (hPipe == INVALID_HANDLE_VALUE)
			throw "Named Pipe can't be created";


		if (!ConnectNamedPipe(hPipe, NULL)) 
			throw "Troubles with client connection";
//соебинение сервера и канала

		while (ReadFile(hPipe, buffer, strlen(buffer) - 1, &dwRead, NULL)!=FALSE)
		{
			buffer[dwRead] = '\0';
			puts(buffer);

			WriteFile(hPipe, buffer, strlen(buffer), &dwRead, NULL);
		}
		//ввод и вывод данных в канал (чтение и запись)
		DisconnectNamedPipe(hPipe); //завершение обмена
		CloseHandle(hPipe); // закрытие дескрипторов
	}
	catch (char* err)
	{
		puts(err);
	}
	delete[] buffer;
	system("pause");
	return 0;
}
