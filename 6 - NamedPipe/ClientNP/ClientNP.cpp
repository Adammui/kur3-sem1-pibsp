#include "pch.h"
#include <iostream>
#include <Winsock2.h>
#define MAX_SIZE_OF_BUFFER 64
#define PIPE TEXT("\\\\.\\pipe\\Tube")

int main()
{
	HANDLE hPipe;
	DWORD dwWritten;
	char* buffer = new char[MAX_SIZE_OF_BUFFER];
	memset(buffer, NULL, MAX_SIZE_OF_BUFFER);
	try
	{
		hPipe = CreateFile(PIPE, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
			throw("Please, check server!");

		WriteFile(hPipe, "Hello Pipe", 12, &dwWritten, NULL);
		ReadFile(hPipe, buffer, MAX_SIZE_OF_BUFFER, &dwWritten, NULL);

		printf("Get from server: %s\n", buffer);
		CloseHandle(hPipe);
	}

	catch (char* err)
	{
		puts(err);
	}
	system("pause");
	return 0;
}














///уст связь:		 симв имя		чт/зап				 РСИ  АБ	флаг открытия	доп А
///hPipe = CreateFile(PIPE, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

///атр безоп не рассм, но они дб один на С и К
//Перед потоком - С и К на одном компе и исп. лок.имена канала
//Перед сообщен - в др. случаях
