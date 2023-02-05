#include "pch.h"
#include <string>
#include "iostream"
#include "windows.h"
#include "time.h"

using namespace std;

string GetErrorMail(int code)
{
	string msgText = "";

	switch (code)
	{
	case WSAEINTR: msgText = "WSAEINTR"; break;
	case WSAEACCES:	msgText = "WSAEACCES"; break;
	case WSAEFAULT:	msgText = "WSAEFAULT"; break;
	default: msgText = "Error";
	};

	return msgText;
}

string SetErrorMail(string msgText, int code)
{
	return msgText + GetErrorMail(code);
}

int main()
{
	setlocale(LC_CTYPE, "Russian");

	cout << "ServerMS" << endl << endl;

	try
	{
		HANDLE hMS;
		double t1, t2;
		int i = 0;

		//созд ПЯ
		///							симв имя		макс длина сообщ	t ожид		атриб безоп
		if ((hMS = CreateMailslot(L"\\\\.\\mailslot\\BOX", 300, MAILSLOT_WAIT_FOREVER, NULL)) == INVALID_HANDLE_VALUE)
			throw SetErrorMail("CreateMailslot", GetLastError());

		char rbuf[100];
		DWORD rms;
		do
		{
			i++;
			//чит д-е из ПЯ (м. т. сервер)
			if (!ReadFile(hMS, rbuf, sizeof(rbuf), &rms, NULL))
				throw SetErrorMail("ReadFile", GetLastError());

			if (i == 1)
				t1 = clock();

			cout << rbuf << endl;
		} while (strcmp(rbuf, " ") != 0);

		t2 = clock();

		cout << "Время передачи: " << (t2 - t1) / 1000 << " сек." << endl;
		cout << "Количество сообщений: " << i - 1 << endl << endl;

		if (!CloseHandle(hMS))
			throw "Error: CloseHandle";

		system("pause");

		HANDLE hms1;

		//откр ПЯ
		/*
		hms1 = CreateFile(L"\\\\ASUS\\mailslot\\zxc", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
		char wbuf[50] = "Jumanji";
		DWORD wms;
		for (int i = 0; i < 1000; i++)
		{
			char q[6];
			sprintf_s(q, "%d", i + 1);
			char buf[sizeof(wbuf) + sizeof(q)];
			strcpy_s(buf, wbuf);
			strcat_s(buf, q);
			//пис д-е в ПЯ
			if (!WriteFile(hms1, buf, sizeof(wbuf), &wms, NULL))
				throw SetErrorMail("WriteFile: ", GetLastError());
			cout << "Message " << i + 1 << endl;
		}
		if (!CloseHandle(hms1))
			throw "Error: CloseHandle";
		system("pause");
		*/
	}
	catch (string e)
	{
		cout << e << endl;
	}

	return 0;
}


///	sH = createMailslot			cH = createFile		//подсоед к ПЯ
///	char rbuf[...]				char wbuf[...]
///								WriteFile
///	ReadFile
///	CloseHandle					CloseHandle			//уничт

///чтобы в 2 стороны - у каждого процесса свой ПЯ
///лок формат:	\\ . \ mailslot \ имя_пя
///сет формат:	\\ servname \ mailslot \ имя_пя
///домен форм:	\\ domain \ mailslot \ имя_пя