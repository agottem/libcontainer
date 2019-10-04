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
#include <container/bst.h>


/* The type we'll be adding to the bst */
struct my_data_entry
{
    char* my_key;
    int   my_value;

    /* Stores bst-specific node data */
    struct container__bst_node node;
};


static enum container__bst_cmp_result
MyBSTLookup (void*, struct container__bst_node* restrict, void*);

static enum container__bst_cmp_result
MyBSTCmp (
          struct container__bst_node* restrict,
          struct container__bst_node* restrict,
          void*
         );


static enum container__bst_cmp_result
MyBSTLookup (void* lookup_key, struct container__bst_node* restrict node, void* user_data)
{
    struct my_data_entry* restrict entry;
    int                            delta;

    entry = CONTAINER__CONTAINER_OF(node, struct my_data_entry, node);

    delta = strcmp(lookup_key, entry->my_key);
    if(delta < 0)
        return container__bst_node_left;
    else if(delta > 0)
        return container__bst_node_right;

    return container__bst_node_equal;
}

static enum container__bst_cmp_result
MyBSTCmp (
          struct container__bst_node* restrict left_node,
          struct container__bst_node* restrict right_node,
          void*                                user_data
         )
{
    struct my_data_entry* restrict left_entry;

    left_entry = CONTAINER__CONTAINER_OF(left_node, struct my_data_entry, node);

    return MyBSTLookup(left_entry->my_key, right_node, user_data);
}


int main (int argument_count, char** arguments)
{
    struct my_data_entry           entries[4];
    struct container__bst_scan     scan;
    struct container__bst          my_bst;
    struct container__bst_node*    closest_node;
    struct my_data_entry* restrict entry;
    enum container__error_code     bst_error;

    Container_InitBST(&my_bst);

    entries[0].my_key   = "the shorter";
    entries[0].my_value = 1962;

    entries[1].my_key   = "the picket line,";
    entries[1].my_value = 1946;

    entries[2].my_key   = "the strike";
    entries[2].my_value = 1835;

    entries[3].my_key   = "The longer";
    entries[3].my_value = 1866;

    for(unsigned int index = 4; index-- > 0;)
        Container_AddBSTNode(&entries[index].node, &my_bst, &MyBSTCmp, NULL);

    for(
        Container_StartBSTScanRight(&my_bst, &scan);
        Container_BSTScanState(&scan) != container__bst_scan_finished;
        Container_ResumeBSTScanRight(&my_bst, &scan)
       )
    {
        entry = CONTAINER__CONTAINER_OF(scan.current_node, struct my_data_entry, node);

        printf("Scanning key: '%s' value: %d\n", entry->my_key, entry->my_value);
    }

    bst_error = Container_LookupBSTNode("the strike", &my_bst, &MyBSTLookup, NULL, &closest_node);
    if(bst_error != container__error_none)
        printf("Could not find key: '%s'\n", "the strike");
    else
    {
        entry = CONTAINER__CONTAINER_OF(closest_node, struct my_data_entry, node);

        printf("Found node key: '%s' value: %d\n", entry->my_key, entry->my_value);
    }

    return EXIT_SUCCESS;
}
