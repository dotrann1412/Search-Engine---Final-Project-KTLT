#ifndef _FileTreeMaker_H
#define _FileTreeMaker_H

#include <Windows.h>
#include "../misc/LinkedList.h"

void listCommand(char* dir, LinkedList& list, int (*criteria)(WIN32_FIND_DATA), int& val);

int isDirectory(WIN32_FIND_DATA x);

int isFile(WIN32_FIND_DATA x);

void listSubfolderInside(char* dir, LinkedList& folderlist, int& val);

void listFileInside(char* dir, LinkedList& filelist, int& val);

void prepareFileTree(char* dir, LinkedList& folderlist, LinkedList*& filelist, int& totalfile);

#endif