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


#ifndef DISPATCHER_H_INCLUDED
#define DISPATCHER_H_INCLUDED


#include <stddef.h>
#include "logicGraph.h"

struct s_dispatcher;
typedef struct s_dispatcher dispatcher;

/**
 * @brief Creates a new dispatcher ready to work on the provided graph.
 *
 * Creates a new dispatcher with an empty job queue ready to act on the graph
 * provided as an argument. This Graph is modified by this action and should
 * only be used with one dispatcher at a time.
 *
 * Note: Crashes on error
 *
 * @param graph *logicGraph   graph to use with the new dispatcher.
 * @param int   threads       number of worker threads to use.
 *
 * @return dispatcher*  Newly created dispatcher.
 */
dispatcher *dispatcherCreate(graph *logicGraph, int threads);

/**
 * @brief Safely Removes dispatcher
 *
 * Deletes dispatcher specified and clears all allocated memory.
 * Leaves internal logicGraph valid and in a safe state.
 *
 * @param dispatcher* Dispatcher to destroy.
 */
void dispatcherDelete(dispatcher *ctx);

/**
 * @brief Steps dispatcher simulation forward by one step.
 *
 * Steps dispatcher simulation forward one step, processing all existing jobs
 * for the current time step and generating future jobs.
 *
 * @param  dispatcher*   dispatcher to step.
 * @return int    		 0 (literally it just returns 0)
 */
int dispatcherStep(dispatcher *ctx);

/**
 * @brief Manually submit a job to the dispatcher (good for inputs)
 *
 * Submit a job for the dispatcher to process in $delay steps from now
 * (now is relative to the dispatcher's internal state). Gate updated is $ID
 *
 * This is particularly useful for updating graph inputs. first set the input's
 * state in the graph then use this command to tell the dispatcher it changed.
 *
 * @param dispatcher     *ctx   dispatcher to use
 * @param unsigned long  ID     ID of gate to update
 * @param unsigned int   delay  how many steps from now to update (min 1)
 *
 * @return int  0 (literally it just returns 0)
 */
int dispatcherAddJob(dispatcher *ctx, size_t ID, unsigned int delay);


#endif
