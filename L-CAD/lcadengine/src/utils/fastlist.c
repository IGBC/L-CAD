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


#include "fastlist.h"

#include <stdlib.h>

struct s_fastlist {
    size_t originalSize;
    size_t currentSize;
    size_t numItems;
    void ** pointer;
};

/** 
 * Create new list
 * Returns FASTLIST_FAILED on failure
 * else returns pointer to list */
fastlist *fastlistCreate(size_t size) {
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
void fastlistDelete(fastlist *ctx) {
    free(ctx->pointer);
    free(ctx);
}

/**
 * Get's <index> element from list 
 * Returns FASTLIST_FAILED if item outside of accepted range 
 * else returns pointer to the index */
void *fastlistGetIndex(fastlist *ctx, size_t index) {
    if (index > ctx->numItems) 
        return (void*) FASTLIST_FAILED;
    return ctx->pointer[index];
}

/**
 * Returns size of the list */
size_t fastlistSize(fastlist *ctx) {
    return ctx->numItems;
}

/**
 * Adds item to the end of the list 
 * Return FASTLIST_FAILED on failure
 * else returns new length of the list */
size_t fastlistAdd(fastlist *ctx, void *item) {
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
void *fastlistRemoveIndex(fastlist *ctx, size_t index) {
    if (index > ctx->numItems) 
        return (void*) FASTLIST_FAILED;
    void *dead = ctx->pointer[index];
    for (size_t i = index + 1; i < ctx->numItems; i++) {
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
size_t fastlistRemoveByPointer(fastlist *ctx, void* pointer) {
    for (size_t i = 0; i < ctx->numItems; i++) {
        if (ctx->pointer[i] == pointer) {
            // We've found our index
            fastlistRemoveIndex(ctx, i);
            return i;
        }
    }
    return FASTLIST_FAILED;
}
