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


#ifndef FASTLIST_H_INCLUDED
#define FASTLIST_H_INCLUDED

#define FASTLIST_FAILED -1
    
typedef struct s_fastlist fastlist;


/**
 * @brief Create new list
 *
 * @returns fastlist            Pointer to a new fastlist
 *                              FASTLIST_FAILED on error
 */
fastlist *fastlistCreate(unsigned long size);


/**
 * @brief Frees resources and deletes list
 *
 * @param fastlist *ctx         An initialised fastlist to work on
 *
 */
void fastlistDelete(fastlist *ctx);


/**
 * @brief Get's <index> element from list 
 *
 * @param fastlist *ctx         An initialised fastlist to work on
 * @param unsigned long index   The index of the item
 *
 * @returns void*               Item from the fastlist
 *                              FASTLIST_FAILED on error
 */
void *fastlistGetIndex(fastlist *ctx, unsigned long index);


/**
 * @brief Returns size of the list
 *
 * @param fastlist *ctx         An initialised fastlist to work on
 *
 * @returns fastlist            Size of the fastlist
 */
unsigned long fastlistSize(fastlist *ctx);


/**
 * @brief Adds item to the end of the list 
 *
 * @param fastlist *ctx         An initialised fastlist to work on
 * @param void *item            Pointer to an item to be added to the list
 *
 * @returns unsigned long       New length of the list
 */
unsigned long fastlistAdd(fastlist *ctx, void *item);


/**
 * @brief Removes item of index from the list and returns it (pop)
 *
 * @param fastlist *ctx         An initialised fastlist to work on
 * @param unsigned long index   The index of the item in the list
 *
 * @returns void*               Item removed from the list (aka POP)
 *                              FASTLIST_FAILED on error
 */
void *fastlistRemoveIndex(fastlist *ctx, unsigned long index);


/**
 * @brief Removes Item from list with matching pointer
 *
 * @param fastlist *ctx         An initialised fastlist to work on
 * @param void *pointer         Pointer to an object in the fastlist
 *
 * @returns unsigned long       Index removed from the fastlist
 *                              FASTLIST_FAILED on error
 */
unsigned long fastlistRemoveByPointer(fastlist *ctx, void* pointer);


/**
 * @brief NOT IMPLEMENTED
 *
 * @param fastlist *ctx         An initialised fastlist to work on
 * @param unsigned long size    Some size
 *
 * @returns void **             Direct pointers to the fastlist
 *                              FASTLIST_FAILED on error
 */
void **fastlistDMA(fastlist *ctx, unsigned long size);

#endif
