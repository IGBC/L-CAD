#include <lcadengine/utils/fastlist.h>

struct s_fastlist {
    unsigned long originalSize;
    unsigned long currentSize;
    unsigned long numItems;
    void ** pointer;
};

fastlist *new_fastlist(unsigned long size) {
    // allocate space for the list
    fastlist *fl = (fastlist*) malloc(sizeof(fastlist));
    if (!fl) return FASTLIST_MALLOC_FAILED;
    // assign initial values
    fl->originalSize = size;
    fl->originalSize = size;
    fl->numItems = 0;
    fl->pointer = malloc(size * sizeof(void *));
    if (!fl->pointer) {
        free(fl);
        return FASTLIST_MALLOC_FAILED;
    }
    return fl;
};

int fastlist_add(fastlist *ctx, void *item);
    // check if full
    if (ctx->numItems == ctx->currentSize) { 
        void ** tmp = (void **) malloc((ctx->currentSize + ctx->originalSize) * sizeof(void *));
        if (!tmp) return FASTLIST_MALLOC_FAILED;
    }
        

