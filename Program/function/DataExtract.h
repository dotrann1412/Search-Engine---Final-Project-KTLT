#ifndef _DataExtract_H
#define _DataExtract_H
#include <stdint.h>
#include "../misc/Structure.h"

void loadingCharacterMap(CharacterMap*& array, uint16_t& size, const char* Path);

void loadingStopword(Stopword*& stopword, uint16_t& stopwordsize, const char* Path);

void loadingComponents(ExtractComponents& stuff);

int compareCriteria(uint16_t*& x, uint16_t xsize, uint16_t*& y, uint16_t ysize);

int searchStopword(uint16_t*& x, uint16_t size, Stopword*& stopword, uint16_t& stopwordsize);

int searchKey(uint16_t x, CharacterMap*& array, uint16_t& size);

void normalizing(uint16_t*& s, int& size, CharacterMap*& normalize, uint16_t& nmlsize);

void toAscii(uint16_t*& s, int& size, CharacterMap*& asciimap, uint16_t& asciisize);

void removeStopword(uint16_t*& s, int& size, Stopword*& stopword, uint16_t& stopwordsize);

void dataExtract(uint16_t*& s, int& size, ExtractComponents& stuff);

#endif