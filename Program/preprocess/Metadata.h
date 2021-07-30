#ifndef _Metadata_H
#define _Metadata_H

#include "../misc/LinkedList.h"
#include "../misc/Structure.h"

void convertLinkedListToChar(Library& lib);

void loadFile(char* dir, LinkedList& folderlist, LinkedList*& filelist, FileRank*& ranklist, ExtractComponents& stuff);

void dataUpdate(char* dir, Library& lib, FileRank*& ranklist, ExtractComponents& stuff);

void addFolder(char* folder, Library& lib);

void deleteFolder(char* folder, Library& lib, FileRank*& ranklist);

void addFile(char* folder, char* filename, Library& lib);

void deleteFile(char* folder, char* filename, Library& lib, FileRank*& ranklist);

void addFileRank(char* dir, char* folder, char* file, FileRank& x, ExtractComponents& stuff);

void optimizeFileTree(char* dir, Library& lib, FileRank*& ranklist, int& ranklistsize, ExtractComponents& stuff);

#endif