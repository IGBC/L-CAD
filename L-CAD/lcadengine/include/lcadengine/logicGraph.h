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


#ifndef LOGICGRAPH_H_INCLUDED
#define LOGICGRAPH_H_INCLUDED

#include <stdbool.h>
#include <lcadengine/fastlist.h>

typedef enum {AND, OR, XOR, UNITY, INPUT, OUTPUT} gateInputType;

struct {
	unsigned long ID; /* Sequential ID of Gate */
	bool state; /* Current Output state for this GLI */
	unsigned int delay; /* Propagation delay of this gate */
	gateInputType inputMode; /* AND OR etc.... */
	bool inputNegate; /* N in front of the mode */
} typedef genericLogicInterface;

struct {
	unsigned long ID; /* ID of this connection */
	genericLogicInterface *srcEp; /* pointer to the GLI of the source */
	genericLogicInterface *drnEp; /* pointer to the GLI of the drain */
	unsigned long srcID; /* ID of the source */
	unsigned long drnID; /* ID of the drain */
} typedef connection;

struct s_graph;
typedef struct s_graph graph;


/**
 * @brief Creates a new logic graph
 *
 * Creates a new, empty logic graph in memory.
 *
 * @return graph                New logic graph
 *                              NULL on error.
 */
graph *graphCreate();


/**
 * @brief Frees a specified logic graph from memory
 *
 * Free a graph and all of of it's attached logic interfaces and
 * connections. The provided graph can not be used after calling
 * this function!
 *
 * @param graph *ctx            The logic graph to be freed
 *
 */
void graphDelete(graph *ctx);


/**
 * @brief Add a new generic logic interface (GLI) to a graph
 *
 * Allocates a new GLI and adds it to a provided logic graph. The
 * id that is returned can be used for future reference.
 *
 * Note: Currently in a state of being fucked up! - IGBC
 *
 * @param graph *ctx            An initialised graph to work on
 * @param gateInputType type    The type of GLI that should be created
 * @param bool nin              Negation state of the GLI
 * @param unsigned long ID      Easy numeric ID used in the graph
 * @param unsigned int delay    The delay this GLI adds
 *
 * @returns ID field provided - identification for the GLI in the graph
 */
unsigned long graphAddGLI(graph *ctx, gateInputType type, bool nin, unsigned long ID, unsigned int delay);


/**
 * @brief Removes a GLI from a provided graph
 *
 * Removes a GLI from a graph and its usage from any connections
 * to other GLIs.
 *
 * @param graph *ctx            An initialised graph to work on
 * @param unsigned long ID      The ID of the GLI to be removed
 *
 */
void graphRemoveGLI(graph *ctx, unsigned long ID);


/**
 * @brief Adds a new connection between two GLIs
 *
 * Requires to working GLI IDs as source and sink to connect them
 * to each other. A connection is always built from source to sink.
 * Returns a numeric ID of the connection for future reference.
 *
 * @param graph *ctx            An initialised graph to work on
 * @param unsigned long Src     Source of the connection
 * @param unsigned long Snk     Sink of the connection
 *
 * @returns ID of the connection for future reference
 */
unsigned long graphAddConnection(graph *ctx, unsigned long Src, unsigned long Snk);


/**
 * @brief Remove connection between two GLIs
 *
 * Simply removes a connection between two GLIs.
 *
 * @param graph *ctx            An initialised graph to work on
 * @param unsigned long ID      Connection Id to removed from the graph
 *
 */
void graphRemoveConnection(graph *ctx, unsigned long ID);


/**
 * @brief Returns the genericLogicInterface from an ID
 *
 * @param graph *ctx              An initialised graph to work on
 * @param unsigned long ID        The ID of a GLI
 *
 * @returns genericLogicInterface Retrieved from the graph.
 *                                NULL on error
 */
genericLogicInterface *graphGetGLI(graph *ctx, unsigned long ID);


/**
 * @brief Returns a GLI connection from an ID
 *
 * @param graph *ctx            An initialised graph to work on
 * @param unsigned long ID      The ID of a connection
 *
 * @returns connection          Retrieved from the graph.
 *                              NULL on error
 */
connection *graphGetConnectionByID(graph *ctx, unsigned long ID);


/**
 * @brief Returns multiple connections from a source ID
 *
 * @param graph *ctx            An initialised graph to work on
 * @param unsigned long ID      The ID of a source GLI
 *
 * @returns fastlist            Connections retrieved from the graph.
 *                              NULL on error
 */
fastlist *graphGetConnectionsBySrc(graph *ctx, unsigned long srcID);


/**
 * @brief Returns multiple connections from a source ID
 *
 * @param graph *ctx              An initialised graph to work on
 * @param unsigned long ID        The ID of a drain GLI
 *
 * @returns fastlist              Connections retrieved from the graph.
 *                                NULL on error
 */
fastlist *graphGetConnectionsByDrn(graph *ctx, unsigned long drnID);


/**
 * @brief Counts all the nodes on the logic graph
 *
 * @param graph *ctx            An initialised graph to work on
 *
 * @Returns unsigned long       Number of nodes on the provided graph
 */
unsigned long graphGetNodeCount(graph *ctx);


/**
 * @brief Prints the provided logic graph as tables
 *
 * @param graph *ctx            An initialised graph to work on
 *
 */
void graphPrint(graph* ctx);

#endif
