#ifndef GRAPHLOADER_H_INCLUDED
#define GRAPHLOADER_H_INCLUDED

#include <lcadengine/logicGraph.h>

/**
 * @brief Creates a graph from the given string.
 *
 * Creates a new logicGraph from a provided graph description string.
 * This function is intended to be used with a string read from a file.
 *
 * @param char *str String to convert to graph. String is unmodified by
 * 					the conversion process.
 *
 * @return logicGraph Graph described by the input string.
 * 					  NULL on error.
 */
graph *loaderLoad(char *str);

#endif
