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


#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED

/** Hashmap structure (forward declaration) */
struct s_hashmap;
typedef struct s_hashmap hashmap;

/** Creates a new hashmap near the given size. */
extern hashmap* hashmapCreate(int startsize);

/** Inserts a new element into the hashmap. */
extern void hashmapInsert(hashmap*, const void* data, unsigned long key);

/** Removes the storage for the element of the key and returns the element. */
extern void* hashmapRemove(hashmap*, unsigned long key);

/** Returns the element for the key. */
extern void* hashmapGet(hashmap*, unsigned long key);

/** Returns the number of saved elements. */
extern long hashmapCount(hashmap*);

/** Removes the hashmap structure. */
extern void hashmapDelete(hashmap*);

#endif

