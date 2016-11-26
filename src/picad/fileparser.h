#ifndef FILEPARSER_H_INCLUDED
#define FILEPARSER_H_INCLUDED

#include "IO.h"
#include "../lcadengine/logicGraph.h" // <- When your library doesn't have a public API

struct {
    graph *g;
    size_t inputCount;
    size_t ouputCount;
    IO_Item *inputs;
    IO_Item *outputs;
} fileInfoDataset;

#endif
