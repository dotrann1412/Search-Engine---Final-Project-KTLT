#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <stdio.h>
#include "InOut.h"
#include "../preprocess/Metadata.h"
#include "../misc/Structure.h"
#include "../misc/Declaration.h"
#include "../preprocess/FileTreeMaker.h"

using namespace std;

void filecopy(char* source, char* dir) {
	fstream fin(source, ios::in | ios::binary);
	string path = string(source);
	string filename = "";
	for (int i = path.size() - 1; path[i] != '\\' && i >= 0; --i) filename += path[i];
	reverse(filename.begin(), filename.end());
	fstream fout(string(dir) + "\\" + filename, ios::out | ios::binary);
	string tmp;

	while (getline(fin, tmp)) tmp += "\n", fout << tmp;


	fin.close(); fout.close();
}

void removedirectory(char dir[]) {
    LinkedList filelist;
    initialize(filelist);
    int count = 0;
    listFileInside(dir, filelist, count);
    Node* cur = filelist.head;
    for (; cur; cur = cur->next) {
        char path[MAX] = "";
        strcpy(path, dir);
        strcat(path, cur->data);
        remove(path);
    }
    RemoveDirectoryA(dir);
    removeAll(filelist);
}

void loadFileContent(char* dir, WCHAR*& content, int CHARACTER_LIMIT)
{
    CHARACTER_LIMIT = 200;
    FILE* fileinput = fopen(dir, "rb");
    if (!fileinput) return;
    fseek(fileinput, 0, SEEK_END);
    int filesize = ftell(fileinput);
    fseek(fileinput, 0, SEEK_SET);

    int res = 0;
    content = new WCHAR[min(int(filesize / sizeof(WCHAR)), CHARACTER_LIMIT) + 1];
    res += fread(content, sizeof(WCHAR), min(CHARACTER_LIMIT, int(filesize / sizeof(WCHAR))), fileinput);

    content[min(int(filesize / sizeof(WCHAR)), CHARACTER_LIMIT)] = '\0';
    fclose(fileinput);
    return;
}

void saveSession(char LibPath[], Library& lib, FileRank*& ranklist)
{
    ofstream out(IndexPath);
    out << LibPath << '\n';
    out << lib.totalfolder << " " << lib.totalfile << '\n';
    for (Node* cur = lib.folderlist.head; cur != NULL; cur = cur->next) {
        out << cur->data << '\n';
        out << cur->index << '\n';
    }

    for (int i = 0; i < lib.totalfolder; ++i) {
        out << lib.filelist[i].size << '\n';
        for (Node* cur = lib.filelist[i].head; cur != nullptr; cur = cur->next) {
            out << cur->data << '\n';
            out << cur->index << '\n';
        }
    }
    for (int i = 0; i < lib.totalfile; ++i) {
        out << ranklist[i].folderindex << " " << ranklist[i].fileindex << " " << ranklist[i].metadatapos << " " << ranklist[i].size << '\n';
    }
    out.close();
}

void loadSession(char LibPath[], Library& lib, FileRank*& ranklist)
{
    ifstream in(IndexPath);
    string st;
    getline(in, st);
    strcpy(LibPath, st.c_str());
    in >> lib.totalfolder >> lib.totalfile;
    in.ignore(1000, '\n');
    for (int i = 0; i < lib.totalfolder; ++i) {
        getline(in, st);
        int x;
        in >> x;
        in.ignore(1000, '\n');
        char* temp = new char[st.length() + 1];
        strcpy(temp, st.c_str());
        addTail(lib.folderlist, temp, x);
        delete[] temp;
    }
    lib.filelist = new LinkedList[lib.totalfolder];
    for (int i = 0; i < lib.totalfolder; ++i) initialize(lib.filelist[i]);
    int x;
    for (int i = 0; i < lib.totalfolder; ++i) {
        in >> x;
        in.ignore(1000, '\n');
        for (int j = 0; j < x; ++j) {
            getline(in, st);
            int x;
            in >> x;
            in.ignore(1000, '\n');
            char* temp = new char[st.length() + 1];
            strcpy(temp, st.c_str());
            addTail(lib.filelist[i], temp, x);
            delete[] temp;
        }
    }
    convertLinkedListToChar(lib);
    ranklist = new FileRank[lib.totalfile];
    for (int i = 0; i < lib.totalfile; ++i) {
        in >> ranklist[i].folderindex >> ranklist[i].fileindex >> ranklist[i].metadatapos >> ranklist[i].size;
    }
    in.close();
}