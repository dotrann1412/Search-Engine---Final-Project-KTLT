#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <string.h>

#include "FileTreeMaker.h"

#include "../misc/LinkedList.h"
#include "../misc/Declaration.h"

#include "../function/Conversion.h"

int isDirectory(WIN32_FIND_DATA x)
{
	return (x.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}

int isFile(WIN32_FIND_DATA x)
{
	return !(x.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}

void listCommand(char* dir, LinkedList& list, int (*criteria)(WIN32_FIND_DATA), int& val)
{
	if (dir[strlen(dir) - 1] != '\\') strcat(dir, "\\");
	char tmp[MAX_PATH];
	strcpy(tmp, dir);
	strcat(tmp, "*");

	WIN32_FIND_DATA ffd;
	WCHAR* wtmp;
	chartoWchar(tmp, wtmp);

	HANDLE hFind = FindFirstFile(wtmp, &ffd);
	char filename[MAX_PATH];
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			wcharToChar(ffd.cFileName, filename);

			if (criteria(ffd) && (filename[strlen(filename) - 1] != '.') && ffd.nFileSizeLow < MAXFILESIZE) {
				++val;
				addTail(list, filename, val);
			}

		} while(FindNextFile(hFind, &ffd)); 
		FindClose(hFind);
	}
	delete[] wtmp;
}

void listSubfolderInside(char* dir, LinkedList& folderlist, int& val)
{
	removeAll(folderlist);
	listCommand(dir, folderlist, isDirectory, val);
}

void listFileInside(char* dir, LinkedList& filelist, int& val)
{
	removeAll(filelist);
	listCommand(dir, filelist, isFile, val);
}

void prepareFileTree(char* dir, LinkedList& folderlist, LinkedList*& filelist, int& totalfile)
{
	initialize(folderlist);
	int val = -1;
	listSubfolderInside(dir, folderlist, val);
	filelist = new LinkedList[folderlist.size];

	for (int i = 0; i < folderlist.size; ++i) initialize(filelist[i]);
	totalfile = 0;
	int count = -1;
	val = -1;
	Node* cur = folderlist.head;
	while (cur) {
		char temp[MAX_PATH];
		strcpy(temp, dir);
		strcat(temp, cur->data);

		count++;
		listFileInside(temp, filelist[count], val);
		totalfile += filelist[count].size;
		cur = cur->next;
	}
}