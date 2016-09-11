#ifndef FASTLIST_H_INCLUDED
#define FASTLIST_H_INCLUDED

#define FASTLIST_FAILED -1
    
typedef struct s_fastlist fastlist;

/** 
 * Create new list
 * Returns FASTLIST_FAILED on failure
 * else returns pointer to list */
fastlist *fastlistCreate(unsigned long size);

/**
 * Frees resources and deletes list */
void fastlistDelete(fastlist *ctx);

/**
 * Get's <index> element from list 
 * Returns FASTLIST_FAILED if item outside of accepted range 
 * else returns pointer to the index */
void *fastlistGetIndex(fastlist *ctx, unsigned long index);

/**
 * Returns size of the list */
unsigned long fastlistSize(fastlist *ctx);

/**
 * Adds item to the end of the list 
 * Return FASTLIST_FAILED on failure
 * else returns new length of the list */
unsigned long fastlistAdd(fastlist *ctx, void *item);

/**
 * Removes item of index from the list
 * Returns FASTLIST_FAILED if index outside of accepted range
 * else returns <SOMETHING> TODO: Work out how this works */
void *fastlistRemoveIndex(fastlist *ctx, unsigned long index);

/** 
 * Removes Item from list with matching pointer
 * Returns FASTLIST_FAILED if pointer not found,
 * else returns index removed */
unsigned long fastlistRemoveByPointer(fastlist *ctx, void* pointer);

/**
 * NOT IMPLEMENTED */
void **fastlistDMA(fastlist *ctx, unsigned long size);

#endif
