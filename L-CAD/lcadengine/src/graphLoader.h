/*
 * This file is part of the L-CAD project
 * Copyright (c) 2016  Ashley Brown, Katharina Sabel
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */


#ifndef GRAPHLOADER_H_INCLUDED
#define GRAPHLOADER_H_INCLUDED

#include "logicGraph.h"

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
