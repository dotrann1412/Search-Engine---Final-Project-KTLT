#ifndef _Structure_H
#define _Structure_H

#include "LinkedList.h"

/// Library
struct Library
{
    LinkedList folderlist;
    LinkedList* filelist;
    char** charfilelist;
    char** charfolderlist;
    int totalfolder;
    int totalfile;
};

void initialize(Library& x);
void deleteAll(Library& x);

/// ExtractComponents

struct CharacterMap
{
    uint16_t key;
    uint16_t value;
};

struct Stopword
{
    uint16_t size;
    uint16_t* value;
};

struct ExtractComponents
{
    uint16_t nmlsize;
    CharacterMap* normalize;
    uint16_t asciisize;
    CharacterMap* asciimap;
    uint16_t delimsize;
    CharacterMap* delimiter;
    uint16_t stopwordsize;
    Stopword* stopword;
};

void initialize(ExtractComponents& x);
void deleteAll(ExtractComponents& x);

/// Ranking

struct FileRank
{
    int folderindex;
    int fileindex;
    int metadatapos;
    int size;
    int score;
};


#endif