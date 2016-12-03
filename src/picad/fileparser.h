#ifndef FILEPARSER_H_INCLUDED
#define FILEPARSER_H_INCLUDED

#include "IO.h"
#include "../lcadengine/base/logicGraph.h" // <- When your library doesn't have a public API

#include <stdlib.h>

struct fileInfoDataset {
    graph *g;
    size_t inputCount;
    size_t outputCount;
    IO_Item **inputs;
    IO_Item **outputs;
};

struct fileInfoDataset parseFile(char *filename);

void cleanFile(struct fileInfoDataset file);

#endif
