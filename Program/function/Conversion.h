#ifndef _Conversion_H
#define _Conversion_H
#include <atlstr.h>

void wcharToChar(WCHAR* x, char* y);
void chartoWchar(char* x, WCHAR*& y);
void wcharToInt16(WCHAR* x, uint16_t*& y);

#endif