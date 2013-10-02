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
#include <container/bal.h>


#define BAL_BUCKET_COUNT 8

#define ENTRY_COUNT 100


/* The type we'll be adding to the clist */
struct my_data_entry
{
    int my_data;

    /* Stores bal-specific node data */
    struct container__bal_node node;
};


int main (int argument_count, char** arguments)
{
    struct my_data_entry         entry_block[ENTRY_COUNT];
    struct container__bal_bucket bal_buckets[BAL_BUCKET_COUNT];
    struct container__bal        my_bal;
    struct container__bal_scan   scan;

    Container_InitBal(BAL_BUCKET_COUNT, bal_buckets, &my_bal);

    for(size_t index = ENTRY_COUNT; index-- > 0;)
    {
        entry_block[index].my_data = index;

        Container_AddBalNode(&entry_block[index].node, &my_bal);
    }

    Container_RemoveBalNode(&entry_block[rand()%ENTRY_COUNT].node, &my_bal);

    for(
        Container_StartBalScanHeavy(&scan, &my_bal);
        Container_BalScanState(&scan, &my_bal) != container__bal_scan_finished;
        Container_ResumeBalScanHeavy(&scan, &my_bal)
       )
    {
        printf("Bucket weight: %d\n", (int)scan.current_bucket->item_count);
    }

    return EXIT_SUCCESS;
}
