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

/*
    The bal container performs a balance of all nodes inserted across a set of buckets.  For
    instance, if there are 5 buckets and 10 nodes are arbitrarily inserted, each bucket will
    contain 2 nodes.  If 2 more nodes are inserted, two of the buckets will have 3 nodes and
    three of the buckets will have 2.

    This is useful for evenly dividing work to be performed across threads
 */


#ifndef _CONTAINER__BAL_H_
#define _CONTAINER__BAL_H_


#include <stddef.h>

#include <container/clist.h>


/*
    Valid states for an individual bucket contained in a bal
 */
enum container__bal_bucket_state
{
    container__bal_bucket_populated,
    container__bal_bucket_empty
};

/*
    Valid states for a scan of a bal
 */
enum container__bal_scan_state
{
    container__bal_scan_incomplete,
    container__bal_scan_finished
};

/*
    Valid states for a scan of a balance bucket
 */
enum container__bal_bucket_scan_state
{
    container__bal_bucket_scan_incomplete,
    container__bal_bucket_scan_finished
};


/*
    The node data to be placed in each bal element
 */
struct container__bal_node
{
    struct container__bal_bucket* bucket;

    struct container__clist_node node;
};

/*
    The buckets which make up the bal container
 */
struct container__bal_bucket
{
    size_t                  item_count;
    struct container__clist item_list;

    struct container__clist_node node;
};

/*
    The bal container itself
 */
struct container__bal
{
    size_t heavy_weight;

    size_t                        bucket_count;
    struct container__bal_bucket* buckets;

    struct container__clist light_list;
    struct container__clist heavy_list;
};

/*
    The scan structure used to scan the buckets of a bal

    Accessible memebers:
       current_bucket -- the current bucket being visited
 */
struct container__bal_scan
{
    struct container__bal_bucket* current_bucket;

    struct container__clist_scan node_scan;
    struct container__clist*     list;
};

/*
    The scan structure used to scan an individual bucket of a balance

    Accessible members:
        current_node -- the current node being visited
 */
struct container__bal_bucket_scan
{
    struct container__bal_node* current_node;

    struct container__clist_scan node_scan;
};


/*
    Initialize a bal.  The container will be empty upon initialization

    Syntax:
        Container_InitBal(number_of_buckets, my_bal_buckets, &my_bal);
 */
inline void
Container_InitBal (
                   size_t,
                   struct container__bal_bucket* restrict,
                   struct container__bal* restrict
                  );

/*
    Reset a bal to its initialized state

    Syntax:
        Container_ResetBal(&my_bal);
 */
inline void
Container_ResetBal (struct container__bal* restrict);


/*
     Merge two bal containers together, invalidating the container being merged from

     Syntax:
         Container_MergeBal(&from_bal, &into_bal);
 */
inline void
Container_MergeBal (struct container__bal* restrict, struct container__bal* restrict);


/*
    Add a node into a bal

    Syntax:
        Container_AddBalNode(&my_element.node, &my_bal);
 */
inline void
Container_AddBalNode (
                      struct container__bal_node* restrict,
                      struct container__bal* restrict
                     );

/*
    Remove a node from a bal

    Syntax:
        Container_RemoveBalNode(&my_element.node, &my_bal);
 */
inline void
Container_RemoveBalNode (
                         struct container__bal_node* restrict,
                         struct container__bal* restrict
                        );


/*
    Return the state of a balance bucket

    Syntax:
        state = Container:BalBucketState(my_bal_buckets[index]);
 */
inline enum container__bal_bucket_state
Container_BalBucketState (struct container__bal_bucket* restrict);


/*
    Begin a bal scan, starting with the lightest buckets

    Syntax:
        Container_StartBalScanLight(&my_bal, &bal_scan);
 */
inline void
Container_StartBalScanLight (
                             struct container__bal* restrict,
                             struct container__bal_scan* restrict
                            );

/*
    Begin a bal scan, starting with the heaviest buckets

    Syntax:
        Container_StartBalScanHeavy(&my_bal, &bal_scan);
 */
inline void
Container_StartBalScanHeavy (
                             struct container__bal* restrict,
                             struct container__bal_scan* restrict
                            );

/*
    Resume a bal scan, visiting the lightest buckets first

    Syntax:
        Container_ResumeBalScanLight(&my_bal, &bal_scan);
 */
inline void
Container_ResumeBalScanLight (
                              struct container__bal* restrict,
                              struct container__bal_scan* restrict
                             );

/*
   Resume a bal scan, visiting the heaviest buckets first

   Syntax:
       Container_ResumeBalScanHeavy(&my_bal, &bal_scan);
 */
inline void
Container_ResumeBalScanHeavy (
                              struct container__bal* restrict,
                              struct container__bal_scan* restrict
                             );

/*
    Return the state of a bal scan

    Syntax:
        state = Container_BalScanState(&my_bal, &bal_scan);
 */
inline enum container__bal_scan_state
Container_BalScanState (
                        struct container__bal* restrict,
                        struct container__bal_scan* restrict
                       );


/*
    Start a scan of an individual bucket

    Syntax:
        Container_StartBalBucketScan(&bal_scan.current_bucket, &bucket_scan);
 */
inline void
Container_StartBalBucketScan (
                              struct container__bal_bucket* restrict,
                              struct container__bal_bucket_scan* restrict
                             );

/*
    Resume the scan of an individual bucket

    Syntax:
        Container_ResumeBalBucketScan(&bal_scan.current_bucket, &bucket_scan);
 */
inline void
Container_ResumeBalBucketScan (
                               struct container__bal_bucket* restrict,
                               struct container__bal_bucket_scan* restrict
                              );

/*
    Return the state of a bucket scan

    Syntax:
        state = Container_BalBucketScanState(&bal_scan.current_bucket, &bucket_scan);
 */
inline enum container__bal_bucket_scan_state
Container_BalBucketScanState (
                              struct container__bal_bucket* restrict,
                              struct container__bal_bucket_scan* restrict
                             );


#include <container/utils.h>


enum container__bal_flags
{
    container__dest_bal_transitioned   = 0x01,
    container__source_bal_transitioned = 0x02
};


inline void
Container_UpdateBalScan (struct container__bal_scan* restrict);

inline void
Container_UpdateBalBucketScan (
                               struct container__bal_bucket* restrict,
                               struct container__bal_bucket_scan* restrict
                              );



inline void
Container_UpdateBalScan (struct container__bal_scan* restrict scan)
{
    enum container__clist_scan_state state;

    state = Container_CListScanState(scan->list, &scan->node_scan);
    if(state == container__clist_scan_incomplete)
    {
        scan->current_bucket = CONTAINER__CONTAINER_OF(
                                                       scan->node_scan.current_node,
                                                       struct container__bal_bucket,
                                                       node
                                                      );
    }
    else
        scan->current_bucket = NULL;
}

inline void
Container_UpdateBalBucketScan (
                               struct container__bal_bucket* restrict      bucket,
                               struct container__bal_bucket_scan* restrict scan
                              )
{
    enum container__clist_scan_state state;

    state = Container_CListScanState(&bucket->item_list, &scan->node_scan);
    if(state == container__clist_scan_incomplete)
    {
        scan->current_node = CONTAINER__CONTAINER_OF(
                                                     scan->node_scan.current_node,
                                                     struct container__bal_node,
                                                     node
                                                    );
    }
    else
        scan->current_node = NULL;
}


inline void
Container_InitBal (
                   size_t                                 bucket_count,
                   struct container__bal_bucket* restrict buckets,
                   struct container__bal* restrict        bal
                  )
{
    bal->heavy_weight = 0;
    bal->bucket_count = bucket_count;
    bal->buckets      = buckets;

    Container_InitCList(&bal->light_list);
    Container_InitCList(&bal->heavy_list);

    for(size_t index = bucket_count; index-- > 0;)
    {
        struct container__bal_bucket* restrict current_bucket;

        current_bucket = &buckets[index];

        current_bucket->item_count = 0;

        Container_InitCList(&current_bucket->item_list);
        Container_AddCListHead(&current_bucket->node, &bal->light_list);
    }
}

inline void
Container_ResetBal (struct container__bal* restrict bal)
{
    Container_InitBal(bal->bucket_count, bal->buckets, bal);
}

inline void
Container_MergeBal (
                    struct container__bal* restrict source,
                    struct container__bal* restrict dest
                   )
{
    struct container__clist     merged_nodes[2];
    struct container__bal_scan  source_scan;
    struct container__bal_scan  dest_scan;
    size_t                      dest_heavy_weight;
    size_t                      source_heavy_weight;
    enum container__bal_flags   flags;
    enum container__clist_state merged_nodes_state[2];
    unsigned int                weight_group;

    weight_group        = 0;
    flags               = 0;
    dest_heavy_weight   = dest->heavy_weight;
    source_heavy_weight = source->heavy_weight;

    Container_InitCList(&merged_nodes[0]);
    Container_InitCList(&merged_nodes[1]);

    Container_StartBalScanHeavy(dest, &dest_scan);
    Container_StartBalScanLight(source, &source_scan);

    do
    {
        struct container__clist_scan           item_scan;
        struct container__bal_bucket* restrict source_bucket;
        struct container__bal_bucket* restrict dest_bucket;

        source_bucket = source_scan.current_bucket;
        dest_bucket   = dest_scan.current_bucket;

        if(
           !(flags&container__dest_bal_transitioned) &&
           dest_bucket->item_count < dest_heavy_weight
          )
        {
            flags        |= container__dest_bal_transitioned;
            weight_group ^= 1;
        }

        if(
           !(flags&container__source_bal_transitioned) &&
           source_bucket->item_count == source_heavy_weight
          )
        {
            flags        |= container__source_bal_transitioned;
            weight_group ^= 1;
        }

        dest_bucket->item_count += source_bucket->item_count;

        for(
            Container_StartCListScanHead(&source_bucket->item_list, &item_scan);
            Container_CListScanState(&source_bucket->item_list, &item_scan) != container__clist_scan_finished;
            Container_ResumeCListScanNext(&item_scan)
           )
        {
            struct container__bal_node* restrict node;

            node = CONTAINER__CONTAINER_OF(
                                           item_scan.current_node,
                                           struct container__bal_node,
                                           node
                                          );

            node->bucket = dest_bucket;
        }

        Container_MergeCListTail(&source_bucket->item_list, &dest_bucket->item_list);

        Container_ResumeBalScanHeavy(dest, &dest_scan);
        Container_ResumeBalScanLight(source, &source_scan);

        Container_RemoveCListNode(&dest_bucket->node);
        Container_AddCListHead(&dest_bucket->node, &merged_nodes[weight_group]);
    }while(Container_BalScanState(source, &source_scan) != container__bal_scan_finished);

    merged_nodes_state[0] = Container_CListState(&merged_nodes[0]);
    merged_nodes_state[1] = Container_CListState(&merged_nodes[1]);

    if(
       merged_nodes_state[0] != container__clist_empty &&
       merged_nodes_state[1] != container__clist_empty
      )
    {
        struct container__bal_bucket* restrict merged_buckets[2];

        merged_buckets[0] = CONTAINER__CONTAINER_OF(
                                                    merged_nodes[0].sentinel.next,
                                                    struct container__bal_bucket,
                                                    node
                                                   );
        merged_buckets[1] = CONTAINER__CONTAINER_OF(
                                                    merged_nodes[1].sentinel.next,
                                                    struct container__bal_bucket,
                                                    node
                                                   );

        if(merged_buckets[0]->item_count > merged_buckets[1]->item_count)
        {
            dest->heavy_weight = merged_buckets[0]->item_count;

            Container_MergeCListHead(&merged_nodes[0], &dest->heavy_list);
            Container_MergeCListHead(&merged_nodes[1], &dest->light_list);
        }
        else
        {
            dest->heavy_weight = merged_buckets[1]->item_count;

            Container_MergeCListHead(&merged_nodes[1], &dest->heavy_list);
            Container_MergeCListHead(&merged_nodes[0], &dest->light_list);
        }
    }
    else
    {
        if(merged_nodes_state[0] != container__clist_empty)
        {
            struct container__bal_bucket* restrict merged_bucket;

            merged_bucket = CONTAINER__CONTAINER_OF(
                                                    merged_nodes[0].sentinel.next,
                                                    struct container__bal_bucket,
                                                    node
                                                   );

            dest->heavy_weight = merged_bucket->item_count;

            Container_MergeCListHead(&merged_nodes[0], &dest->heavy_list);
        }
        else
        {
            struct container__bal_bucket* restrict merged_bucket;

            merged_bucket = CONTAINER__CONTAINER_OF(
                                                    merged_nodes[1].sentinel.next,
                                                    struct container__bal_bucket,
                                                    node
                                                   );

            dest->heavy_weight = merged_bucket->item_count;

            Container_MergeCListHead(&merged_nodes[1], &dest->heavy_list);
        }
    }
}

inline void
Container_AddBalNode (
                      struct container__bal_node* restrict node,
                      struct container__bal* restrict      bal
                     )
{
    struct container__bal_bucket* restrict bucket;
    enum container__clist_state            state;

    state = Container_CListState(&bal->light_list);
    if(state == container__clist_empty)
    {
        bucket = CONTAINER__CONTAINER_OF(
                                         bal->heavy_list.sentinel.next,
                                         struct container__bal_bucket,
                                         node
                                        );

        Container_SplitCListAfter(&bucket->node, &bal->heavy_list, &bal->light_list);
    }
    else
    {
        bucket = CONTAINER__CONTAINER_OF(
                                         bal->light_list.sentinel.next,
                                         struct container__bal_bucket,
                                         node
                                        );

        Container_RemoveCListNode(&bucket->node);
        Container_AddCListHead(&bucket->node, &bal->heavy_list);
    }

    Container_AddCListHead(&node->node, &bucket->item_list);

    bucket->item_count++;

    node->bucket = bucket;

    bal->heavy_weight = bucket->item_count;
}

inline void
Container_RemoveBalNode (
                         struct container__bal_node* restrict node,
                         struct container__bal* restrict      bal
                        )
{
    struct container__bal_bucket* restrict bucket;

    bucket = node->bucket;

    Container_RemoveCListNode(&node->node);

    if(bucket->item_count < bal->heavy_weight)
    {
        enum container__clist_state state;

        state = Container_CListState(&bal->heavy_list);
        if(state == container__clist_empty)
        {
            bal->heavy_weight = bucket->item_count;
            bucket->item_count--;

            Container_MergeCListHead(&bal->light_list, &bal->heavy_list);
            Container_RemoveCListNode(&bucket->node);
            Container_ResetCList(&bal->light_list);
            Container_AddCListHead(&bucket->node, &bal->light_list);
        }
        else
        {
            struct container__bal_bucket* restrict moved_bucket;
            struct container__bal_node* restrict   moved_node;

            moved_bucket = CONTAINER__CONTAINER_OF(
                                                   bal->heavy_list.sentinel.next,
                                                   struct container__bal_bucket,
                                                   node
                                                  );

            moved_node = CONTAINER__CONTAINER_OF(
                                                 moved_bucket->item_list.sentinel.next,
                                                 struct container__bal_node,
                                                 node
                                                );

            Container_RemoveCListNode(&moved_node->node);
            Container_AddCListHead(&moved_node->node, &bucket->item_list);
            Container_RemoveCListNode(&moved_bucket->node);
            Container_AddCListHead(&moved_bucket->node, &bal->light_list);

            moved_node->bucket = bucket;
            moved_bucket->item_count--;
        }
    }
    else
    {
        bucket->item_count--;

        Container_RemoveCListNode(&bucket->node);
        Container_AddCListHead(&bucket->node, &bal->light_list);
    }
}

inline enum container__bal_bucket_state
Container_BalBucketState (struct container__bal_bucket* restrict bucket)
{
    if(bucket->item_count > 0)
        return container__bal_bucket_populated;

    return container__bal_bucket_empty;
}

inline void
Container_StartBalScanLight (
                             struct container__bal* restrict      bal,
                             struct container__bal_scan* restrict scan
                            )
{
    scan->list = &bal->light_list;

    Container_StartCListScanHead(&bal->light_list, &scan->node_scan);
    Container_UpdateBalScan(scan);

    if(scan->current_bucket == NULL)
    {
        scan->list = &bal->heavy_list;

        Container_StartCListScanHead(&bal->heavy_list, &scan->node_scan);

        scan->current_bucket = CONTAINER__CONTAINER_OF(
                                                       scan->node_scan.current_node,
                                                       struct container__bal_bucket,
                                                       node
                                                      );
    }
}

inline void
Container_StartBalScanHeavy (
                             struct container__bal* restrict      bal,
                             struct container__bal_scan* restrict scan
                            )
{
    scan->list = &bal->heavy_list;

    Container_StartCListScanHead(&bal->heavy_list, &scan->node_scan);
    Container_UpdateBalScan(scan);

    if(scan->current_bucket == NULL)
    {
        scan->list = &bal->light_list;

        Container_StartCListScanHead(&bal->light_list, &scan->node_scan);

        scan->current_bucket = CONTAINER__CONTAINER_OF(
                                                       scan->node_scan.current_node,
                                                       struct container__bal_bucket,
                                                       node
                                                      );
    }
}

inline void
Container_ResumeBalScanLight (
                              struct container__bal* restrict      bal,
                              struct container__bal_scan* restrict scan
                             )
{
    Container_ResumeCListScanNext(&scan->node_scan);
    Container_UpdateBalScan(scan);

    if(scan->current_bucket == NULL && scan->list == &bal->light_list)
    {
        scan->list = &bal->heavy_list;

        Container_StartCListScanHead(&bal->heavy_list, &scan->node_scan);
        Container_UpdateBalScan(scan);
    }
}

inline void
Container_ResumeBalScanHeavy (
                              struct container__bal* restrict      bal,
                              struct container__bal_scan* restrict scan
                             )
{
    Container_ResumeCListScanNext(&scan->node_scan);
    Container_UpdateBalScan(scan);

    if(scan->current_bucket == NULL && scan->list == &bal->heavy_list)
    {
        scan->list = &bal->light_list;

        Container_StartCListScanHead(&bal->light_list, &scan->node_scan);
        Container_UpdateBalScan(scan);
    }
}

inline enum container__bal_scan_state
Container_BalScanState (
                        struct container__bal* restrict      bal,
                        struct container__bal_scan* restrict scan
                       )
{
    if(scan->current_bucket == NULL)
        return container__bal_scan_finished;

    return container__bal_scan_incomplete;
}

inline void
Container_StartBalBucketScan (
                              struct container__bal_bucket* restrict      bucket,
                              struct container__bal_bucket_scan* restrict scan
                             )
{
    Container_StartCListScanHead(&bucket->item_list, &scan->node_scan);
    Container_UpdateBalBucketScan(bucket, scan);
}

inline void
Container_ResumeBalBucketScan (
                               struct container__bal_bucket* restrict      bucket,
                               struct container__bal_bucket_scan* restrict scan
                              )
{
    Container_ResumeCListScanNext(&scan->node_scan);
    Container_UpdateBalBucketScan(bucket, scan);
}

inline enum container__bal_bucket_scan_state
Container_BalBucketScanState (
                              struct container__bal_bucket* restrict      bucket,
                              struct container__bal_bucket_scan* restrict scan
                             )
{
    if(scan->current_node == NULL)
        return container__bal_bucket_scan_finished;

    return container__bal_bucket_scan_incomplete;
}


#endif
