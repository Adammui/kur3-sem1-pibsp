#include "pch.h"
#include <iostream>
#include <Winsock2.h>
#define PIPE TEXT("\\\\.\\pipe\\Tube")
#define MAX_SIZE_OF_BUFFER 64

int main()
{
	DWORD bytes;
	char buffer[] = "Hello Pipe";
	char* outbuffer = new char[MAX_SIZE_OF_BUFFER];
	memset(outbuffer, NULL, MAX_SIZE_OF_BUFFER);
	try
	{
		CallNamedPipe(PIPE, buffer, sizeof(buffer), outbuffer, MAX_SIZE_OF_BUFFER, &bytes, NMPWAIT_WAIT_FOREVER); //1 t
		puts(outbuffer);
	}
	catch (char* err)
	{
		puts(err);
	}
	delete[] outbuffer;
	system("pause");
	return 0;
}



















///если надо передать т. 1 транз
///уст связи -> отпр 1 сообщ -> получ 1 сообщ -> разрыв связь