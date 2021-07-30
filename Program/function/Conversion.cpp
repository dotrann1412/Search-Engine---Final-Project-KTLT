#include <atlstr.h>
#include <iostream>

#include "Conversion.h"
#include "../misc/Declaration.h"

using namespace std;

void wcharToChar(WCHAR* x, char *y)
{
    int i = 0;
    while (x[i] != '\0')
    {
        y[i] = (char)x[i];
        ++i;
    }
    y[i] = '\0';
}


void chartoWchar(char* x, WCHAR*& y)
{
	int size = MultiByteToWideChar(CP_ACP, 0, x, -1, NULL, 0);
	y = new WCHAR[MAX];
	MultiByteToWideChar(CP_ACP, 0, x, -1, (LPWSTR)y, size);
}

void wcharToInt16(WCHAR* x, uint16_t*& y)
{
    int len = wcslen(x);
    y = new uint16_t[len];
    for (int i = 0; i < len; ++i) y[i] = static_cast<uint16_t>(x[i]);
}