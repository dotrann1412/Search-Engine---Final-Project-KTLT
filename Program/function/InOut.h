#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "../misc/Structure.h"

void filecopy(char*, char*);

void loadFileContent(char* dir, WCHAR*& content, int CHARACTER_LIMIT);

void saveSession(char LibPath[], Library& lib, FileRank*& ranklist);

void loadSession(char LibPath[], Library& lib, FileRank*& ranklist);

void removedirectory(char dir[]);
