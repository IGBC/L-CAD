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


#include "minUnit.h"
#include "../src/utils/hashmap.h"

void test_hashmap() {
    mu_run_test(test_hashmap_insert);
    mu_run_test(
}

char *test_hashmap_insert() {
    unsigned long key = 1;
    int * value = 123456789;
    
    hashmap map = hashmapCreate(1021);
    hashmapInsert(hashmap, (void*) value, key);
    void *returned = hashmapGet(hashmap, key);
    
    return mu_assert("insert test", ((void*)value == returned));    
}

test_hashmap_multinsert_profit() {
    
}
