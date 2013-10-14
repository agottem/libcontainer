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
#include <container/utils.h>
#include <container/slist.h>


#define ENTRY_COUNT 100


/* The type we'll be adding to the slist */
struct my_data_entry
{
    int my_data;

    /* Stores slist-specific node data */
    struct container__slist_node node;
};


int main (int argument_count, char** arguments)
{
    struct my_data_entry         entry_block[ENTRY_COUNT];
    struct container__slist      my_list;
    struct container__slist_scan scan;

    Container_InitSList(&my_list);

    for(int count = ENTRY_COUNT; count-- > 0;)
    {
        entry_block[count].my_data = count;

        Container_AddSListHead(&entry_block[count].node, &my_list);
    }

    for(
        Container_StartSListScan(&my_list, &scan);
        Container_SListScanState(&scan) != container__slist_scan_finished;
        Container_ResumeSListScan(&scan)
       )
    {
        struct my_data_entry* restrict entry;

        entry = CONTAINER__CONTAINER_OF(scan.current_node, struct my_data_entry, node);

        printf("Visited entry: %d\n", entry->my_data);
    }

    return EXIT_SUCCESS;
}
