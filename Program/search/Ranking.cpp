#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <stdint.h>

#include "Ranking.h"

#include "../misc/Declaration.h"
#include "../misc/Structure.h"
#include "../function/DataExtract.h"

void initialize(FileRank& x, int folderindex, int fileindex, int size, int pos)
{
    x.folderindex = folderindex;
    x.fileindex = fileindex;
    x.metadatapos = pos;
    x.size = size;
    x.score = 0;
}

int compareCriteria(FileRank x, FileRank y)
{
    if (x.score != y.score) return x.score > y.score;
    return x.fileindex < y.fileindex;
}

void mergeRankList(FileRank*& left, int n, FileRank*& right, int m, FileRank*& combine)
{
    combine = new FileRank[n + m];
    int il = 0, ir = 0;
    for (int i = 0; i < n + m; ++i) {
        if (il >= n) combine[i] = right[ir++];
        else if (ir >= m) combine[i] = left[il++];
        else combine[i] = (compareCriteria(left[il], right[ir])) ? left[il++] : right[ir++];
    }
}

void sortRankList(FileRank*& ranklist, int totalfile)
{
    if (totalfile == 1) return;
    else {
        int half = totalfile / 2;
        FileRank* left = ranklist;
        FileRank* right = ranklist + half;
        sortRankList(left, half);
        sortRankList(right, totalfile - half);
        FileRank* temp;
        mergeRankList(left, half, right, totalfile - half, temp);
        for (int i = 0; i < totalfile; ++i) ranklist[i] = temp[i];
        delete[] temp;
    }
}

int scoreRating(int x, int keywordlen)
{
    if (x == keywordlen) return 100;
    if (10 * x >= 9 * keywordlen) return 90 * x / keywordlen;
    if (10 * x >= 8 * keywordlen) return 50 * x / keywordlen;
    if (10 * x >= 7 * keywordlen) return 30 * x / keywordlen;
    if (10 * x >= 6 * keywordlen) return 20 * x / keywordlen;
    return 0;
}


void matchingFunction(uint16_t* s, int n, int m, int* match, int& score)
{
    match[0] = 0;
    int prev = 0;
    for (int i = 1; i < n; ++i) {
        int j = prev;
        while (j > 0 && s[i] != s[j]) j = match[j - 1];
        if (s[i] == s[j]) ++j;
        prev = j;
        if (i < m) match[i] = j;
        score += scoreRating(j, m);
    }
}

void calcScore(uint16_t*& userinput, int inputlen, FileRank*& ranklist, int totalfile, ExtractComponents& stuff)
{
    FILE* in = nullptr;
    in = fopen(MetadataPath, "rb");
    if (in == nullptr) return;
    fseek(in, 2, SEEK_SET);

    static uint16_t* buffer = nullptr;
    int* match = new int[inputlen];
    int maxsize = 0;
    for (int i = 0; i < totalfile; ++i) maxsize = std::max(maxsize, ranklist[i].size);
    buffer = new uint16_t[inputlen + 1 + maxsize / (int)sizeof(uint16_t)];
    for (int i = 0; i < inputlen; ++i) buffer[i] = userinput[i];
    buffer[inputlen] = UnreachUnicode;

    for (int i = 0; i < totalfile; ++i)
    {
        fseek(in, ranklist[i].metadatapos, SEEK_SET);
        fread(buffer + inputlen + 1, sizeof(uint16_t), (int)(ranklist[i].size / sizeof(uint16_t)), in);
        int bufferlen = inputlen + 1 + ranklist[i].size / (int)sizeof(uint16_t);
        ranklist[i].score = 0;
        matchingFunction(buffer, bufferlen, inputlen, match, ranklist[i].score);
        int size = bufferlen * sizeof(uint16_t);
        toAscii(buffer, size, stuff.asciimap, stuff.asciisize);
        matchingFunction(buffer, bufferlen, inputlen, match, ranklist[i].score);
    }

    fclose(in);
    delete[] buffer;
}
void searchFile(uint16_t*& userinput, int inputlen, FileRank*& ranklist, int totalfile, ExtractComponents& stuff)
{
    calcScore(userinput, inputlen, ranklist, totalfile, stuff);
    sortRankList(ranklist, totalfile);
}



