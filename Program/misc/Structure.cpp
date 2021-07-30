#include <stdint.h>

#include "Structure.h"
#include "LinkedList.h"

/// Library

void initialize(Library& x)
{
    initialize(x.folderlist);
    x.filelist = nullptr;
    x.charfilelist = nullptr;
    x.charfolderlist = nullptr;
    x.totalfile = 0;
    x.totalfolder = 0;
}

void deleteAll(Library& x)
{
    for (int i = 0; i < x.totalfolder; ++i) removeAll(x.filelist[i]);
    delete[] x.filelist;
    removeAll(x.folderlist);
    for (int i = 0; i < x.totalfile; ++i) delete[] x.charfilelist[i];
    delete[] x.charfilelist;
    for (int i = 0; i < x.totalfolder; ++i) delete[] x.charfolderlist[i];
    delete[] x.charfolderlist;
    x.totalfile = 0;
    x.totalfolder = 0;
}

/// ExtractComponents

void initialize(ExtractComponents& x)
{
    x.nmlsize = 0;
    x.normalize = nullptr;
    x.asciisize = 0;
    x.asciimap = nullptr;
    x.delimsize = 0;
    x.delimiter = nullptr;
    x.stopwordsize = 0;
    x.stopword = nullptr;
}

void deleteAll(ExtractComponents& x)
{
    x.nmlsize = 0;
    delete[] x.normalize;
    x.asciisize = 0;
    delete[] x.asciimap;
    x.delimsize = 0;
    delete[] x.delimiter;
    for (int i = 0; i < x.stopwordsize; ++i) delete[] x.stopword[i].value;
    delete[] x.stopword;
}