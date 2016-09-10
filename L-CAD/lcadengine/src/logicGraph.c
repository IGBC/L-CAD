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
    for (i = 0; i < fastlistSize(ctx->connections); i++) {
        connection *conn = (connection*) fastlistGetIndex(ctx->connections, i);
        graphRemoveConnection(ctx, conn->ID);
    }
    
    // delete Nodes
    for (i = 0; i < fastlistSize(ctx->nodes); i++) {
        GLI *gli = (GLI*) fastlistGetIndex(ctx->nodes, i);
        graphRemoveGLI(ctx, gli->ID);
    }
    
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
    
    ctx->nodeCount++;
    return gli->ID;
    // gli goes out of scope here. (psst, don't tell anyone the ID is a pointer)
};

void graphRemoveGLI(graph *ctx, unsigned long ID) {
    //Unregister this GLI;
    GLI *gli = (GLI*) hashmapRemove(ctx->GIDMap, ID);
    fastlistRemoveByPointer(ctx->nodes, gli);
    
    //TODO Remove connections here.
    
    free(gli);
    ctx->nodeCount--;
};

unsigned long graphAddConnection(graph *ctx, unsigned long src, unsigned long drn) {
    connection *conn = (connection*) malloc(sizeof(connection));
    conn->ID = (unsigned long) conn; // We're using the pointer as a UUID, as we don't have a generator.
    // TODO: Generate Better IDs
    
    GLI* srcGli = (GLI*) hashmapGet(ctx->GIDMap, src); 
    GLI* drnGli = (GLI*) hashmapGet(ctx->GIDMap, drn); 
    
    conn->srcEp = srcGli;
    conn->drnEp = drnGli;
    conn->srcID = src;
    conn->drnID = drn;
    
    //insert into Connection ID map;
    hashmapInsert(ctx->CIDMap, (void*)conn, conn->ID);
    fastlistAdd(ctx->connections, (void*)conn);
    
    //check to see if a connection already exists with this src
    fastlist* list = (fastlist*) hashmapGet(ctx->srcMap, src);
    if (!list) { //if the list doesn't exist
        list = fastlistCreate(CONN_LIST_SIZE);
        //TODO: safety this;
        hashmapInsert(ctx->srcMap, (void*)list, src);
    }
    //add the Connection to the list;
    fastlistAdd(list, (void*)conn);

    //check to see if a connection already exists with this drn
    list = (fastlist*) hashmapGet(ctx->drnMap, drn);
    if (!list) { //if the list doesn't exist
        list = fastlistCreate(CONN_LIST_SIZE);
        //TODO: safety this;
        hashmapInsert(ctx->drnMap, (void*)list, drn);
    }
    //add the Connection to the list;
    fastlistAdd(list, (void*)conn);

    return conn->ID;
};

void graphRemoveConnection(graph *ctx, unsigned long ID) {
    // Remove Connection from hashmap
    connection *conn = (connection*) hashmapRemove(ctx->CIDMap, ID);
    
    // Remove connection from Source and drain map/lists
    // NOTE: This might leak. if the lists are empty
    fastlist *list = (fastlist*) hashmapGet(ctx->srcMap, conn->srcID);
    fastlistRemoveByPointer(list, (void*)conn);
    list = (fastlist*) hashmapGet(ctx->drnMap, conn->drnID);
    fastlistRemoveByPointer(list, (void*)conn);
    
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
