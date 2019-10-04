/*
    The C container library is licensed under the simplified BSD license:

    Copyright 2013, Andrew Gottemoller
    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of
    conditions and the following disclaimer:

    Redistributions in binary form must reproduce the above copyright notice, this list
    of conditions and the following disclaimer in the documentation and/or other materials
    provided with the distribution.

    Neither the name Andrew Gottemoller nor the names of its contributors may be used to
    endorse or promote products derived from this software without specific prior written
    permission.
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <container/utils.h>
#include <container/hash.h>


#define HASH_BUCKET_COUNT 256


/* The type we'll be adding to the hash */
struct my_data_entry
{
    char* my_key;
    int   my_value;

    /* Stores hash-specific node data */
    struct container__hash_node node;
};


static inline unsigned int
KeyHashValue (char* restrict);

static enum container__hash_cmp_result
MyHashLookup (void*, struct container__hash_node* restrict, void*);


static inline unsigned int
KeyHashValue (char* restrict key)
{
    return key[0];
}

static enum container__hash_cmp_result
MyHashLookup (void* lookup_key, struct container__hash_node* restrict cmp_node, void* user_data)
{
    struct my_data_entry* restrict entry;

    entry = CONTAINER__CONTAINER_OF(cmp_node, struct my_data_entry, node);

    if(strcmp(lookup_key, entry->my_key) == 0)
        return container__hash_node_equal;

    return container__hash_node_not_equal;
}


int main (int argument_count, char** arguments)
{
    struct my_data_entry           entries[4];
    struct container__hash_bucket  hash_buckets[HASH_BUCKET_COUNT];
    struct container__hash         my_hash;
    struct container__hash_bucket* searched_bucket;
    struct container__hash_node*   found_node;
    struct my_data_entry* restrict found_entry;

    Container_InitHash(HASH_BUCKET_COUNT, hash_buckets, &my_hash);

    entries[0].my_key   = "c";
    entries[0].my_value = 1337;

    entries[1].my_key   = "is the";
    entries[1].my_value = 80085;

    entries[2].my_key   = "language of";
    entries[2].my_value = 666;

    entries[3].my_key   = "gods";
    entries[3].my_value = 3;

    for(unsigned int index = 4; index-- > 0;)
        Container_AddHashNode(KeyHashValue(entries[index].my_key), &entries[index].node, &my_hash);

    found_node = Container_LookupHashNode(
                                          KeyHashValue("gods"),
                                          "gods",
                                          &my_hash,
                                          &MyHashLookup,
                                          NULL,
                                          &searched_bucket
                                         );

    found_entry = CONTAINER__CONTAINER_OF(found_node, struct my_data_entry, node);

    printf("Found hash node with key: '%s', value: %d\n", found_entry->my_key, found_entry->my_value);

    return EXIT_SUCCESS;
}
