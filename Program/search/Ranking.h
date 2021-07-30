#ifndef _Ranking_H
#define _Ranking_H

#include <stdint.h>
#include "../misc/Structure.h"

const int RankSize = 100;

const int UnreachUnicode = 65535;

void initialize(FileRank& x, int folderindex, int fileindex, int size, int pos);

int compareCriteria(FileRank x, FileRank y);

void mergeRankList(FileRank*& left, int n, FileRank*& right, int m, FileRank*& combine);

void sortRankList(FileRank*& ranklist, int totalfile);

int scoreRating(int x, int keywordlen);

void matchingFunction(uint16_t* s, int n, int m, int* match, int& score);

void calcScore(uint16_t*& userinput, int inputlen, FileRank*& ranklist, int totalfile, ExtractComponents& stuff);

void searchFile(uint16_t*& userinput, int inputlen, FileRank*& ranklist, int totalfile, ExtractComponents& stuff);

#endif

