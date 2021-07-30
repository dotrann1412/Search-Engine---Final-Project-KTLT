#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>

#include "Metadata.h"
#include "FileTreeMaker.h"

#include "../misc/Declaration.h"
#include "../misc/LinkedList.h"
#include "../misc/Structure.h"

#include "../function/DataExtract.h"

#include "../search/Ranking.h"

void convertLinkedListToChar(Library& lib)
{
    if (lib.charfolderlist != nullptr) delete[] lib.charfolderlist;
    if (lib.charfilelist != nullptr) delete[] lib.charfilelist;

    lib.charfolderlist = new char* [lib.totalfolder];

    for (Node* folder = lib.folderlist.head; folder != NULL; folder = folder->next) {
        lib.charfolderlist[folder->index] = new char[strlen(folder->data) + 1];
        strcpy(lib.charfolderlist[folder->index], folder->data);
    }

    lib.charfilelist = new char* [lib.totalfile];

    for (Node* folder = lib.folderlist.head; folder != NULL; folder = folder->next) {
        for (Node* file = lib.filelist[folder->index].head; file != NULL; file = file->next) {
            lib.charfilelist[file->index] = new char[strlen(file->data) + 1];
            strcpy(lib.charfilelist[file->index], file->data);
        }
    }
}

void loadFile(char* dir, LinkedList& folderlist, LinkedList*& filelist, FileRank*& ranklist, ExtractComponents& stuff)
{
    FILE* in = nullptr, * out = nullptr;
    out = fopen(MetadataPath, "wb");
    if (out == nullptr) return;

    uint16_t utf16bit = 65279;
    fwrite(&utf16bit, sizeof(uint16_t), 1, out);

    int count = -1;
    int cur = -1;
    char path[MAX_PATH];

    static uint16_t* info = nullptr;

    for (Node* folder = folderlist.head; folder != NULL; folder = folder->next)
    {
        ++count;
        for (Node* file = filelist[count].head; file != NULL; file = file->next)
        {          
            ++cur;
            strcpy(path, dir);
            strcat(path, folder->data);
            strcat(path, "\\");
            strcat(path, file->data);

            int res = 0;
            if (info != nullptr) delete[] info;

            in = fopen(path, "rb");
            if (in == nullptr) continue;

            fseek(in, 0, SEEK_END);
            int filesize = ftell(in) - 2;
            fseek(in, 2, SEEK_SET);

            info = new uint16_t[(int)(filesize / sizeof(uint16_t))];

            while (1) {
                int p = fread(info + res, sizeof(uint16_t), min(MAX, (int)(filesize / sizeof(uint16_t)) - res), in);
                res += p;
                if (p < MAX) break;
            }
            dataExtract(info, filesize, stuff);
            int pos = ftell(out);
            initialize(ranklist[cur], count, cur, filesize, pos);
            fwrite(info, sizeof(uint16_t), (int)(filesize / sizeof(uint16_t)), out);

            fclose(in);
        }
    }
    fclose(out);
}

void dataUpdate(char* dir, Library& lib, FileRank*& ranklist, ExtractComponents& stuff)
{
    prepareFileTree(dir, lib.folderlist, lib.filelist, lib.totalfile);
    lib.totalfolder = lib.folderlist.size;

    convertLinkedListToChar(lib);

    if (ranklist != nullptr) delete[] ranklist;
    ranklist = new FileRank[lib.totalfile];

    loadFile(dir, lib.folderlist, lib.filelist, ranklist, stuff);
}

void addFolder(char* folder, Library& lib)
{
    addTail(lib.folderlist, folder, lib.totalfolder);
    lib.totalfolder++;
    LinkedList* temp = lib.filelist;
    lib.filelist = new LinkedList[lib.totalfolder];
    for (int i = 0; i < lib.totalfolder - 1; ++i) lib.filelist[i] = temp[i];
    initialize(lib.filelist[lib.totalfolder - 1]);
}

void deleteFolder(char* folder, Library& lib, FileRank*& ranklist)
{
    int folderindex = 0;
    for (Node* cur = lib.folderlist.head; cur != nullptr; cur = cur->next) {
        if (strcmp(cur->data, folder) == 0) {
            folderindex = cur->index;
            removeI(lib.folderlist, cur);
            break;
        }
    }

    removeAll(lib.filelist[folderindex]);
    lib.filelist[folderindex].size = -1;

    for (int i = 0; i < lib.totalfile; ++i) {
        if (ranklist[i].folderindex == folderindex) {
            ranklist[i].size = -1;
        }
    }
}

void addFile(char* folder, char* filename, Library& lib)
{
    int folderindex = 0;
    for (Node* cur = lib.folderlist.head; cur != nullptr; cur = cur->next) {
        if (strcmp(cur->data, folder) == 0) {
            folderindex = cur->index;
            break;
        }
    }

    addTail(lib.filelist[folderindex], filename, lib.totalfile);
    lib.totalfile++;
}

void deleteFile(char* folder, char* filename, Library& lib, FileRank*& ranklist)
{
    int folderindex = 0;

    for (Node* cur = lib.folderlist.head; cur != nullptr; cur = cur->next) {
        if (strcmp(cur->data, folder) == 0) {
            folderindex = cur->index;
            break;
        }
    }

    int fileindex = 0;

    for (Node* cur = lib.filelist[folderindex].head; cur != nullptr; cur = cur->next) {
        if (strcmp(cur->data, filename) == 0) {
            fileindex = cur->index;
            removeI(lib.filelist[folderindex], cur);
            break;
        }
    }

    for (int i = 0; i < lib.totalfile; ++i) {
        if (ranklist[i].folderindex == folderindex && ranklist[i].fileindex == fileindex) {
            ranklist[i].size = -1;
            break;
        }
    }
}

void addFileRank(char* dir, char* folder, char* file, FileRank& x, ExtractComponents& stuff)
{
    FILE* in = nullptr, * out = nullptr;
    out = fopen(MetadataPath, "ab");
    if (out == nullptr) return;

    fseek(out, 0, SEEK_END);
    x.metadatapos = ftell(out);

    char path[MAX_PATH];
    uint16_t* info = nullptr;

    strcpy(path, dir);
    strcat(path, "\\");
    strcat(path, folder);
    strcat(path, "\\");
    strcat(path, file);

    int res = 0;

    in = fopen(path, "rb");
    if (in == nullptr) return;

    fseek(in, 0, SEEK_END);
    int filesize = ftell(in) - 2;
    fseek(in, 2, SEEK_SET);

    info = new uint16_t[(int)(filesize / sizeof(uint16_t))];

    while (1) {
        int p = fread(info + res, sizeof(uint16_t), min(MAX, (int)(filesize / sizeof(uint16_t)) - res), in);
        res += p;
        if (p < MAX) break;
    }
    dataExtract(info, filesize, stuff);
    x.size = filesize;
    fwrite(info, sizeof(uint16_t), (int)(filesize / sizeof(uint16_t)), out);

    fclose(in);
    fclose(out);
    delete[] info;
}

void optimizeFileTree(char* dir, Library& lib, FileRank*& ranklist, int& ranklistsize, ExtractComponents& stuff)
{
    int foldernum = lib.totalfolder;
    int filenum = lib.totalfile;
    int* newfolderindex = new int[foldernum];
    for (int i = 0; i < foldernum; ++i) newfolderindex[i] = 0;
    int val = -1;
    lib.totalfolder = lib.folderlist.size;
    for (Node* cur = lib.folderlist.head; cur != nullptr; cur = cur->next) {
        ++val;
        newfolderindex[cur->index] = val;
        cur->index = val;
    }

    LinkedList* oldfilelist = lib.filelist;
    lib.filelist = new LinkedList[lib.totalfolder];
    val = -1;
    for (int i = 0; i < foldernum; ++i) {
        if (oldfilelist[i].size == -1) continue;
        ++val;
        lib.filelist[val] = oldfilelist[i];
    }

    FileRank* newranklist = new FileRank[filenum - ranklistsize];
    int* newfileindex = new int[filenum];
    for (int i = 0; i < filenum; ++i) newfileindex[i] = 0;
    lib.totalfile = -1;
    val = -1;
    for (Node* folder = lib.folderlist.head; folder != nullptr; folder = folder->next) {
        for (Node* file = lib.filelist[folder->index].head; file != nullptr; file = file->next) {
            ++lib.totalfile;
            newfileindex[file->index] = lib.totalfile;
            if (file->index >= ranklistsize) {
                ++val;
                initialize(newranklist[val], folder->index, lib.totalfile, 0, 0);
            }
            file->index = lib.totalfile;
        }
    }
    ++lib.totalfile;

    convertLinkedListToChar(lib);


    FileRank* oldranklist = ranklist;
    ranklist = new FileRank[lib.totalfile];
    val = -1;

    for (int i = 0; i < filenum; ++i) {
        if (i < ranklistsize) {
            if (oldranklist[i].size == -1) continue;
            ++val;
            initialize(ranklist[val], newfolderindex[oldranklist[i].folderindex], newfileindex[oldranklist[i].fileindex], oldranklist[i].size, oldranklist[i].metadatapos);
        }
        else {
            ++val;
            FileRank tmp = newranklist[i - ranklistsize];
            addFileRank(dir, lib.charfolderlist[tmp.folderindex], lib.charfilelist[tmp.fileindex], tmp, stuff);
            initialize(ranklist[val], tmp.folderindex, tmp.fileindex, tmp.size, tmp.metadatapos);
        }
    }
    delete[] newranklist;
    delete[] oldranklist;
    delete[] oldfilelist; 
    delete[] newfolderindex;
    delete[] newfileindex;
}
