// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include "error.h"

#include <string>
#include <string.h>
#include <iostream>
#include <ctime>
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib") 

using std::string;
using std::cout;
using std::sin;
using std::cin;
using std::endl;


// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
