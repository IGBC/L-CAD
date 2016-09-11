#include <lcadengine/logicGraph.h>

#include <stdlib.h>

#include "utils/hashmap.h"

#define GLI genericLogicInterface
#define CONN_LIST_SIZE 5

struct s_graph {
	hashmap *GIDMap; // Gates
	hashmap *CIDMap, *srcMap, *drnMap; // Connections
	fastlist *nodes, *connections;
	unsigned long nodeCount;
};

graph *graphCreate() {
    graph *ctx = (graph*) malloc(sizeof(graph));
    ctx->GIDMap = hashmapCreate(0);
    ctx->CIDMap = hashmapCreate(0);
    ctx->srcMap = hashmapCreate(0);
    ctx->drnMap = hashmapCreate(0);
    ctx->nodes = fastlistCreate(CONN_LIST_SIZE);
    ctx->connections = fastlistCreate(CONN_LIST_SIZE);
    ctx->nodeCount = 0;
    return ctx;
};

void graphDelete(graph *ctx) {
    unsigned long i;
    // delete Connections
    do {
        connection *conn = (connection*) fastlistGetIndex(ctx->connections, 0);
        graphRemoveConnection(ctx, conn->ID);
    } while (fastlistSize(ctx->connections) > 0);

    // delete Nodes
    do {
        GLI *gli = (GLI*) fastlistGetIndex(ctx->nodes, 0);
        graphRemoveGLI(ctx, gli->ID);
    } while (fastlistSize(ctx->nodes) > 0);

    // tear down the graph
    hashmapDelete(ctx->GIDMap);
    hashmapDelete(ctx->CIDMap);
    hashmapDelete(ctx->srcMap);
    hashmapDelete(ctx->drnMap);
    fastlistDelete(ctx->nodes);
    fastlistDelete(ctx->connections);
    free(ctx);
};

unsigned long graphAddGLI(graph *ctx, gateInputType type, bool nin, unsigned int delay) {
    GLI *gli = (GLI*) malloc(sizeof(GLI));

    gli->ID = (unsigned long) gli; // We're using the pointer as a UUID, as we don't have a generator.
    // TODO: Generate Better IDs
    gli->state = false; // All GLI's start off
    // Just copy this across.
    gli->delay = delay;
    gli->inputMode = type;
    gli->inputNegate = nin;

    // Push gli into the map
    hashmapInsert(ctx->GIDMap, (void*)gli, gli->ID);
    fastlistAdd(ctx->nodes, (void*)gli);

    // Create Connection Lists for SRC and DRN for this gate
    fastlist * srcList = fastlistCreate(CONN_LIST_SIZE);
    //TODO: safety this;
    hashmapInsert(ctx->srcMap, (void*)srcList, gli->ID);
    fastlist *drnList = fastlistCreate(CONN_LIST_SIZE);
    //TODO: safety this;
    hashmapInsert(ctx->drnMap, (void*)drnList, gli->ID);


    //Construction complete, cleanup;

    ctx->nodeCount++;
    return gli->ID;
    // gli goes out of scope here. (psst, don't tell anyone the ID is a pointer)
};

void graphRemoveGLI(graph *ctx, unsigned long ID) {
    //Unregister this GLI;
    GLI *gli = (GLI*) hashmapRemove(ctx->GIDMap, ID);
    fastlistRemoveByPointer(ctx->nodes, gli);

    // Get Connection lists
    fastlist *srcList = (fastlist*) hashmapGet(ctx->srcMap, ID);
    fastlist *drnList = (fastlist*) hashmapGet(ctx->drnMap, ID);

    // Remove src connections here.
    {
        unsigned long count = fastlistSize(srcList);
        for (unsigned long i = 0; i < count; i++) {
            // Get the connection.
            connection *conn = (connection *) fastlistGetIndex(srcList, i);
            unsigned long index = conn->ID;
            // Remove it
            graphRemoveConnection(ctx, index);
        }
    }

    // Remove drn connections here.
    {
        unsigned long count = fastlistSize(drnList);
        for (unsigned long i = 0; i < count; i++) {
            // Get the connection.
            connection *conn = (connection *) fastlistGetIndex(drnList, i);
            unsigned long index = conn->ID;
            // Remove it
            graphRemoveConnection(ctx, index);
        }
    }

    // Free the connection lists.
    hashmapRemove(ctx->srcMap, ID);
    hashmapRemove(ctx->drnMap, ID);
    fastlistDelete(srcList);
    fastlistDelete(drnList);

    // Done, cleanup

    free(gli);
    ctx->nodeCount--;
};

unsigned long graphAddConnection(graph *ctx, unsigned long src, unsigned long drn) {
    // TODO: safety this
    connection *conn = (connection*) malloc(sizeof(connection));


    conn->ID = (unsigned long) conn; // We're using the pointer as a UUID, as we don't have a generator.
    // TODO: Generate Better IDs

    GLI* srcGli = (GLI*) hashmapGet(ctx->GIDMap, src);
    GLI* drnGli = (GLI*) hashmapGet(ctx->GIDMap, drn);

    conn->srcEp = srcGli;
    conn->drnEp = drnGli;
    conn->srcID = src;
    conn->drnID = drn;

    // insert into Connection ID map;
    hashmapInsert(ctx->CIDMap, (void*)conn, conn->ID);
    fastlistAdd(ctx->connections, (void*)conn);

    // add the Connection to the srcList;
    fastlist *srcList = (fastlist*) hashmapGet(ctx->srcMap, src);
    fastlistAdd(srcList, (void*)conn);

    // add the Connection to the drnList;
    fastlist *drnList = (fastlist*) hashmapGet(ctx->drnMap, drn);
    fastlistAdd(drnList, (void*)conn);

    // done, cleanup

    return conn->ID;
};

void graphRemoveConnection(graph *ctx, unsigned long ID) {
    // Remove Connection from hashmap
    connection *conn = (connection*) hashmapRemove(ctx->CIDMap, ID);

    // Remove connection from Source and drain map/lists
    fastlist *drnList = (fastlist*) hashmapGet(ctx->srcMap, conn->srcID);
    fastlistRemoveByPointer(drnList, (void*)conn);
    fastlist *srcList = (fastlist*) hashmapGet(ctx->drnMap, conn->drnID);
    fastlistRemoveByPointer(srcList, (void*)conn);

    // Remove the Connection from main list
    fastlistRemoveByPointer(ctx->connections, conn);

    // Finally free the Connection
    free(conn);
}

genericLogicInterface *graphGetGLI(graph *ctx, unsigned long ID) {
    return (GLI*) hashmapGet(ctx->GIDMap, ID);
}

connection *graphGetConnectionByID(graph *ctx, unsigned long ID) {
    return (connection*) hashmapGet(ctx->CIDMap, ID);
}

fastlist *graphGetConnectionsBySrc(graph *ctx, unsigned long srcID) {
    return (fastlist*) hashmapGet(ctx->srcMap, srcID);
}

fastlist *graphGetConnectionsByDrn(graph *ctx, unsigned long drnID) {
    return (fastlist*) hashmapGet(ctx->drnMap, drnID);
}

unsigned long graphGetNodeCount(graph *ctx){
    return ctx->nodeCount;
}
