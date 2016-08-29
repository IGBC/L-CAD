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
