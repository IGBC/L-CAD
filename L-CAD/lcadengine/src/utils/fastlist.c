#include <lcadengine/fastlist.h>
#include <stdlib.h>

struct s_fastlist {
    unsigned long originalSize;
    unsigned long currentSize;
    unsigned long numItems;
    void ** pointer;
};

/** 
 * Create new list
 * Returns FASTLIST_FAILED on failure
 * else returns pointer to list */
fastlist *new_fastlist(unsigned long size) {
    // allocate space for the list
    fastlist *fl = (fastlist*) malloc(sizeof(fastlist));
    if (!fl) return (fastlist*) FASTLIST_FAILED;
    // assign initial values
    fl->originalSize = size;
    fl->currentSize = size;
    fl->numItems = 0;
    fl->pointer = malloc(size * sizeof(void *));
    if (!fl->pointer) {
        free(fl);
        return (fastlist*) FASTLIST_FAILED;
    }
    return fl;
};

/**
 * Frees resources and deletes list */
void fastlist_dispose(fastlist *ctx) {
    free(ctx->pointer);
    free(ctx);
}

/**
 * Get's <index> element from list 
 * Returns FASTLIST_FAILED if item outside of accepted range 
 * else returns pointer to the index */
void *fastlist_get(fastlist *ctx, unsigned long index) {
    if (index > ctx->numItems) 
        return (void*) FASTLIST_FAILED;
    return ctx->pointer[index];
}

/**
 * Returns size of the list */
unsigned long fastlist_size(fastlist *ctx) {
    return ctx->numItems;
}

/**
 * Adds item to the end of the list 
 * Return FASTLIST_FAILED on failure
 * else returns new length of the list */
unsigned long fastlist_add(fastlist *ctx, void *item) {
    // Check if full
    if (ctx->numItems == ctx->currentSize) { 
        // New size is number of desired pointers * size of a pointer
        void ** tmp = (void **) realloc(ctx->pointer, (ctx->currentSize + ctx->originalSize) * sizeof(void *));
        if (!tmp) return FASTLIST_FAILED;
        ctx->currentSize += ctx->originalSize;
        ctx->pointer = tmp;
    }

    // Insert data into da hood 
    ctx->pointer[ctx->numItems++] = item;
    return ctx->numItems;
}

/**
 * Removes item of index from the list and returns it.
 * Returns FASTLIST_FAILED if index outside of accepted range
 * else retuŕns <SOMETHING> TODO: Work out how this works */
void *fastlist_remove(fastlist *ctx, unsigned long index) {
    if (index > ctx->numItems) 
        return (void*) FASTLIST_FAILED;
    void *dead = ctx->pointer[index];
    for (unsigned long i = index + 1; i < ctx->numItems; i++) {
        ctx->pointer[i-1] = ctx->pointer[i];
    };
    ctx->numItems--;

    // If the array has significant empty space.
    if ((ctx->currentSize - ctx->numItems) > (ctx->originalSize * 1.5)) {
        void ** tmp = (void **) realloc(ctx->pointer, (ctx->currentSize - ctx->originalSize) * sizeof(void *));
        if (!tmp) return (void*) FASTLIST_FAILED;
        ctx->currentSize -= ctx->originalSize;
        ctx->pointer = tmp;
    }
    return dead;
}

/** 
 * Removes Item from list with matching pointer
 * Returns FASTLIST_FAILED if pointer not found,
 * else returns index removed */
unsigned long fastlist_remove_by_pointer(fastlist *ctx, void* pointer) {
    for (unsigned long i = 0; i < ctx->numItems; i++) {
        if (ctx->pointer[i] == pointer) {
            // We've found our index
            fastlist_remove(ctx, i);
            return i;
        }
    }
    return FASTLIST_FAILED;
}

/**
 * NOT IMPLEMENTED */
//void **fastlist_dma(fastlist *ctx, unsigned long size);
