#include <lcadengine/logicGraph.h>

#include <stdlib.h>

#include "utils/hashmap.h"

#define GLI genericLogicInterface
#define CONN_LIST_SIZE 5

struct s_graph {
	hashmap *GIDMap; // Gates
	hashmap *CIDMap, *srcMap, *drnMap; // Connections
	unsigned long nodeCount;
};

graph *create_graph() {
    graph *ctx = (graph*) malloc(sizeof(graph));
    ctx->GIDMap = hashmapCreate(0);
    ctx->CIDMap = hashmapCreate(0);
    ctx->srcMap = hashmapCreate(0);
    ctx->drnMap = hashmapCreate(0);
    ctx->nodeCount = 0;
    return ctx;
};

void delete_graph(graph *ctx) {
    hashmapDelete(ctx->GIDMap);
    hashmapDelete(ctx->CIDMap);
    hashmapDelete(ctx->srcMap);
    hashmapDelete(ctx->drnMap);
    free(ctx);
};

unsigned long add_gli(graph *ctx, gateInputType type, bool nin, unsigned int delay) {
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
    ctx->nodeCount++;
    return gli->ID;
    // gli goes out of scope here. (psst, don't tell anyone the ID is a pointer)
};

void remove_gli(graph *ctx, unsigned long ID) {
    GLI *gli = (GLI*) hashmapRemove(ctx->GIDMap, ID);
    //TODO Remove connections here.
    free(gli);
    ctx->nodeCount--;
};

unsigned long add_conn(graph *ctx, unsigned long src, unsigned long drn) {
    connection *conn = (connection*) malloc(sizeof(connection));
    conn->ID = (unsigned long) conn; // We're using the pointer as a UUID, as we don't have a generator.
    // TODO: Generate Better IDs
    
    GLI* srcGli = (GLI*) hashmapGet(ctx->GIDMap, src); 
    GLI* drnGli = (GLI*) hashmapGet(ctx->GIDMap, drn); 
    
    conn->srcEp = srcGli;
    conn->srcEp = drnGli;
    conn->srcID = src;
    conn->drnID = drn;
    
    //insert into Connection ID map;
    hashmapInsert(ctx->CIDMap, (void*)conn, conn->ID);
    
    //check to see if a connection already exists with this src
    fastlist* list = (fastlist*) hashmapGet(ctx->srcMap, src);
    if (!list) { //if the list doesn't exist
        list = new_fastlist(CONN_LIST_SIZE);
        //TODO: safety this;
        hashmapInsert(ctx->srcMap, (void*)list, src);
    }
    //add the Connection to the list;
    fastlist_add(list, (void*)conn);

    //check to see if a connection already exists with this drn
    list = (fastlist*) hashmapGet(ctx->drnMap, drn);
    if (!list) { //if the list doesn't exist
        list = new_fastlist(CONN_LIST_SIZE);
        //TODO: safety this;
        hashmapInsert(ctx->drnMap, (void*)list, drn);
    }
    //add the Connection to the list;
    fastlist_add(list, (void*)conn);

    return conn->ID;
};

void remove_conn(graph *ctx, unsigned long ID) {
    connection *conn = (connection*) hashmapRemove(ctx->CIDMap, ID);
    fastlist *list = (fastlist*) hashmapGet(ctx->srcMap, conn->srcID);
    fastlist_remove_by_pointer(list, (void*)conn);
    list = (fastlist*) hashmapGet(ctx->drnMap, conn->drnID);
    fastlist_remove_by_pointer(list, (void*)conn);
}

genericLogicInterface *get_gli(graph *ctx, unsigned long ID) {
    return (GLI*) hashmapGet(ctx->GIDMap, ID);
}

connection *get_conn_by_id(graph *ctx, unsigned long ID) {
    return (connection*) hashmapGet(ctx->CIDMap, ID);
}

fastlist *get_conns_by_src(graph *ctx, unsigned long srcID) {
    return (fastlist*) hashmapGet(ctx->srcMap, srcID);
}

fastlist *get_conns_by_drn(graph *ctx, unsigned long drnID) {
    return (fastlist*) hashmapGet(ctx->srcMap, drnID);
}

unsigned long get_node_count(graph *ctx){
    return ctx->nodeCount;
}
