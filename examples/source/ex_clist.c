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
#include <container/clist.h>


#define ENTRY_COUNT 100


/* The type we'll be adding to the clist */
struct my_data_entry
{
    int my_data;

    /* Stores clist-specific node data */
    struct container__clist_node node;
};


int main (int argument_count, char** arguments)
{
    struct my_data_entry         entry_block[ENTRY_COUNT];
    struct container__clist      my_list;
    struct container__clist      split_list;
    struct container__clist_scan scan;

    Container_InitCList(&my_list);

    for(int count = ENTRY_COUNT; count-- > 0;)
    {
        entry_block[count].my_data = count;

        if(count%2 == 1)
            Container_AddCListHead(&entry_block[count].node, &my_list);
        else
            Container_AddCListTail(&entry_block[count].node, &my_list);
    }

    Container_SplitCListAfter(&entry_block[rand()%ENTRY_COUNT].node, &my_list, &split_list);

    Container_RemoveCListNode(&entry_block[rand()%ENTRY_COUNT].node);

    for(
        Container_StartCListScanHead(&my_list, &scan);
        Container_CListScanState(&my_list, &scan) != container__clist_scan_finished;
        Container_ResumeCListScanNext(&scan)
       )
    {
        struct my_data_entry* restrict entry;

        entry = CONTAINER__CONTAINER_OF(scan.current_node, struct my_data_entry, node);

        printf("Visited entry: %d\n", entry->my_data);
    }

    for(
        Container_StartCListScanTail(&split_list, &scan);
        Container_CListScanState(&split_list, &scan) != container__clist_scan_finished;
        Container_ResumeCListScanPrev(&scan)
       )
    {
        struct my_data_entry* restrict entry;

        entry = CONTAINER__CONTAINER_OF(scan.current_node, struct my_data_entry, node);

        printf("Split-list visited entry: %d\n", entry->my_data);
    }

    return EXIT_SUCCESS;
}
