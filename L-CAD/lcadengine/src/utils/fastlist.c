#include <lcadengine/utils/fastlist.h>

struct s_fastlist {
    unsigned long originalSize;
    unsigned long currentSize;
    unsigned long numItems;
};

fastlist *new_fastlist(unsigned long size) {
    // allocate space for the list
    fastlist *fl = (fastlist*) malloc(sizeof(fastlist) + size);
    // assign initial values
    fl->originalSize = size;
    fl->originalSize = size;
    fl->numItems = 0;
    return fl;
};

int fastlist_add(&fastlist *ctx, void** item);
    // check if full
    if (ctx->numItems == currentSize) 

