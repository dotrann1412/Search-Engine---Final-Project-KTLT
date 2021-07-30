#include <iostream>

#include "DataExtract.h"
#include "../misc/Declaration.h"
#include "../misc/Structure.h"

void loadingCharacterMap(CharacterMap*& array, uint16_t& size, const char* Path)
{
    FILE* in = nullptr;
    in = fopen(Path, "rb");
    if (in == nullptr) return;

    fseek(in, 0, SEEK_END);
    int filesize = ftell(in) - 2;
    fseek(in, 2, SEEK_SET);
    size = filesize / sizeof(uint16_t) / 2;
    array = new CharacterMap[size];

    int cur = 0;
    while (1) {
        int p = fread(&array[cur], sizeof(CharacterMap), 1, in);
        cur++;
        if (!p) break;
    }

    fclose(in);
}

void loadingStopword(Stopword*& stopword, uint16_t& stopwordsize, const char* Path)
{
    FILE* in = nullptr;
    in = fopen(Path, "rb");
    if (in == nullptr) return;

    uint16_t endline1 = 13;
    uint16_t endline2 = 10;
    fseek(in, 2, SEEK_SET);
    fread(&stopwordsize, sizeof(uint16_t), 1, in);
    fseek(in, 8, SEEK_SET);
    int mask = 100;

    stopword = new Stopword[stopwordsize];

    for (int i = 0; i < stopwordsize; ++i) {
        fread(&stopword[i].size, sizeof(uint16_t), 1, in);
        stopword[i].size -= mask;
        stopword[i].value = new uint16_t[stopword[i].size];
        fread(stopword[i].value, sizeof(uint16_t), stopword[i].size, in);
        fread(&endline1, sizeof(uint16_t), 1, in);
        fread(&endline2, sizeof(uint16_t), 1, in);
    }

    fclose(in);
}

void loadingComponents(ExtractComponents& stuff)
{
    loadingCharacterMap(stuff.normalize, stuff.nmlsize, NormalizePath);
    loadingCharacterMap(stuff.asciimap, stuff.asciisize, AsciiPath);
    loadingCharacterMap(stuff.delimiter, stuff.delimsize, DelimiterPath);
    loadingStopword(stuff.stopword, stuff.stopwordsize, StopwordPath);
}

int compareCriteria(uint16_t*& x, uint16_t xsize, uint16_t*& y, uint16_t ysize)
{
    for (int i = 0; i < std::min(xsize, ysize); ++i) {
        if (x[i] > y[i]) return 1;
        if (x[i] < y[i]) return -1;
    }
    if (xsize > ysize) return 1;
    if (xsize < ysize) return -1;
    return 0;
}

int searchStopword(uint16_t*& x, uint16_t size, Stopword*& stopword, uint16_t& stopwordsize)
{
    int left = 0; int right = stopwordsize - 1;
    while (left <= right) {
        int mid = (left + right) >> 1;
        int p = compareCriteria(x, size, stopword[mid].value, stopword[mid].size);
        if (p != -1) {
            if (p == 0) return mid;
            left = mid + 1;
        }
        else right = mid - 1;
    }
    return -1;
}

int searchKey(uint16_t x, CharacterMap*& array, uint16_t& size)
{
    int left = 0; int right = size - 1;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (array[mid].key <= x) {
            if (array[mid].key == x) return mid;
            left = mid + 1;
        }
        else right = mid - 1;
    }
    return -1;
}

void normalizing(uint16_t*& s, int& size, CharacterMap*& normalize, uint16_t& nmlsize)
{
    int n = size / sizeof(uint16_t);
    for (int i = 0; i < n; ++i) {
        int p = searchKey(s[i], normalize, nmlsize);
        if (p != -1) s[i] = normalize[p].value;
    }
}

void toAscii(uint16_t*& s, int& size, CharacterMap*& asciimap, uint16_t& asciisize)
{
    int n = size / sizeof(uint16_t);
    for (int i = 0; i < n; ++i) {
        int p = searchKey(s[i], asciimap, asciisize);
        if (p != -1) s[i] = asciimap[p].value;
    }
}

void tokenizing(uint16_t*& s, int& size, CharacterMap*& delimiter, uint16_t& delimsize)
{
    int n = size / sizeof(uint16_t);
    int* temp = new int[n];
    int newn = n;
    int cur = -1;
    for (int i = 0; i < n; ++i) {
        temp[i] = 2;
        int p = searchKey(s[i], delimiter, delimsize);
        if (p != -1) {
            s[i] = delimiter[p].value;
            if (i == 0 || temp[i - 1] != 2) temp[i] = 1, --newn; else temp[i] = 0;
        }
        else cur = i;
    }
    if (cur != n - 1) --newn, temp[cur + 1] = 1;
    uint16_t* t = s;
    s = new uint16_t[newn];
    size = newn * sizeof(uint16_t);
    newn = 0;
    for (int i = 0; i < n; ++i) {
        if (temp[i] != 1) s[newn] = t[i], ++newn;
    }
    delete[] t;
    delete[] temp;
}

void removeStopword(uint16_t*& s, int& size, Stopword*& stopword, uint16_t& stopwordsize)
{
    int n = size / sizeof(uint16_t);
    int* temp = new int[n];
    int start[4]{ 0 };
    int nstart = 0;
    for (int i = 0; i < n; ++i)  temp[i] = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 32 || i == n - 1) {
            for (int j = nstart; j >= 0; --j) {
                uint16_t* sub = s + start[j];
                int p = searchStopword(sub, i - start[j] + (i == n - 1), stopword, stopwordsize);
                if (p != -1) {
                    temp[start[j]] += 1;
                    if (i != n - 1) temp[i] += -1;
                    nstart = -1;
                    break;
                }
            }
            if (nstart < 3) nstart++;
            for (int j = nstart; j > 0; --j) start[j] = start[j - 1];
            start[0] = i + 1;
        }
    }
    int newn = 0;
    for (int i = 1; i < n; ++i) temp[i] += temp[i - 1];
    for (int i = 0; i < n; ++i) {
        if (temp[i] != 1 && s[i] != 32) ++newn;
    }
    uint16_t* t = s;
    s = new uint16_t[newn];
    size = newn * sizeof(uint16_t);
    newn = 0;
    for (int i = 0; i < n; ++i) {
        if (temp[i] != 1 && t[i] != 32) {
            s[newn] = t[i];
            ++newn;
        }
    }

    delete[] t;
    delete[] temp;
}

void dataExtract(uint16_t*& s, int& size, ExtractComponents& stuff)
{
    normalizing(s, size, stuff.normalize, stuff.nmlsize);
    tokenizing(s, size, stuff.delimiter, stuff.delimsize);
    removeStopword(s, size, stuff.stopword, stuff.stopwordsize);
}


