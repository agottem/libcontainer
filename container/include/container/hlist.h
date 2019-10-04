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
    The hlist container manages a hash of elements and tandem with a list of those elements
 */


#ifndef _CONTAINER__HLIST_H_
#define _CONTAINER__HLIST_H_


#include <container/clist.h>
#include <container/hash.h>


enum container__hlist_cmp_result
{
    container__hlist_node_not_equal,
    container__hlist_node_equal
};

enum container__hlist_state
{
    container__hlist_populated,
    container__hlist_empty
};

enum container__hlist_bucket_scan_state
{
    container__hlist_bucket_scan_incomplete,
    container__hlist_bucket_scan_finished
};

enum container__hlist_scan_state
{
    container__hlist_scan_incomplete,
    container__hlist_scan_finished
};


struct container__hlist_node
{
    struct container__clist_node list_node;
    struct container__hash_node  hash_node;
};

struct container__hlist
{
    struct container__clist list;
    struct container__hash  hash;
};

struct container__hlist_bucket_scan
{
    struct container__hlist_node* current_node;

    struct container__hash_bucket_scan node_scan;
};

struct container__hlist_scan
{
    struct container__hlist_node* current_node;

    struct container__clist_scan node_scan;
};


typedef enum container__hlist_cmp_result
(*container__hlist_lookup_type) (
                                 void*,
                                 struct container__hlist_node* restrict,
                                 void*
                                );


inline void
Container_InitHList (
                     unsigned int,
                     struct container__hash_bucket* restrict,
                     struct container__hlist* restrict
                    );

inline void
Container_ResetHList (struct container__hlist* restrict);


inline struct container__hash_bucket*
Container_LookupHListBucket (unsigned int, struct container__hlist* restrict);

inline struct container__hlist_node*
Container_LookupHListNode (
                           unsigned int,
                           void*,
                           struct container__hlist* restrict,
                           container__hlist_lookup_type,
                           void*,
                           struct container__hash_bucket** restrict
                          );


inline void
Container_AddHListNode (
                        unsigned int,
                        struct container__hlist_node* restrict,
                        struct container__hlist* restrict
                       );

inline void
Container_InsHListNode (
                        struct container__hlist_node* restrict,
                        struct container__hash_bucket* restrict,
                        struct container__hlist* restrict
                       );

inline void
Container_RemoveHListNode (struct container__hlist_node* restrict);


inline enum container__hlist_state
Container_HListState (struct container__hlist* restrict);


inline void
Container_StartHListBucketScan (
                                struct container__hash_bucket* restrict,
                                struct container__hlist_bucket_scan* restrict
                               );

inline void
Container_ResumeHListBucketScan (
                                 struct container__hash_bucket* restrict,
                                 struct container__hlist_bucket_scan* restrict
                                );

inline enum container__hlist_bucket_scan_state
Container_HListBucketScanState (struct container__hlist_bucket_scan* restrict);


inline void
Container_StartHListScanNode (
                              struct container__hlist_node* restrict,
                              struct container__hlist* restrict,
                              struct container__hlist_scan* restrict
                             );

inline void
Container_StartHListScanHead (
                              struct container__hlist* restrict,
                              struct container__hlist_scan* restrict
                             );

inline void
Container_StartHListScanTail (
                              struct container__hlist* restrict,
                              struct container__hlist_scan* restrict
                             );

inline void
Container_ResumeHListScanNext (
                               struct container__hlist* restrict,
                               struct container__hlist_scan* restrict
                              );

inline void
Container_ResumeHListScanPrev (
                               struct container__hlist* restrict,
                               struct container__hlist_scan* restrict
                              );

inline enum container__hlist_scan_state
Container_HListScanState (struct container__hlist_scan* restrict);


#include <container/utils.h>


struct container__hlist_hash_lookup_data
{
    void*                        user_data;
    container__hlist_lookup_type lookup;
};


inline enum container__hash_cmp_result
Container_HListHashLookup (void*, struct container__hash_node* restrict, void*);


inline void
Container_UpdateHListBucketScan (struct container__hlist_bucket_scan* restrict);

inline void
Container_UpdateHListScan (
                           struct container__hlist* restrict,
                           struct container__hlist_scan* restrict
                          );


inline enum container__hash_cmp_result
Container_HListHashLookup (
                           void*                                 value,
                           struct container__hash_node* restrict hash_node,
                           void*                                 user_data
                          )
{
    struct container__hlist_hash_lookup_data* restrict hlist_hash_lookup;
    struct container__hlist_node*                      hlist_node;
    enum container__hlist_cmp_result                   result;

    hlist_hash_lookup = user_data;
    hlist_node        = CONTAINER__CONTAINER_OF(
                                                hash_node,
                                                struct container__hlist_node,
                                                hash_node
                                               );

    result = (*hlist_hash_lookup->lookup)(value, hlist_node, hlist_hash_lookup->user_data);
    if(result == container__hlist_node_not_equal)
        return container__hash_node_not_equal;

    return container__hash_node_equal;
}


inline void
Container_UpdateHListBucketScan (struct container__hlist_bucket_scan* restrict scan)
{
    enum container__hash_bucket_scan_state state;

    state = Container_HashBucketScanState(&scan->node_scan);
    if(state == container__hash_bucket_scan_incomplete)
    {
        scan->current_node = CONTAINER__CONTAINER_OF(
                                                     scan->node_scan.current_node,
                                                     struct container__hlist_node,
                                                     hash_node
                                                    );
    }
    else
        scan->current_node = NULL;
}

inline void
Container_UpdateHListScan (
                           struct container__hlist* restrict      hlist,
                           struct container__hlist_scan* restrict scan
                          )
{
    enum container__clist_scan_state state;

    state = Container_CListScanState(&hlist->list, &scan->node_scan);
    if(state == container__clist_scan_incomplete)
    {
        scan->current_node = CONTAINER__CONTAINER_OF(
                                                     scan->node_scan.current_node,
                                                     struct container__hlist_node,
                                                     list_node
                                                    );
    }
    else
        scan->current_node = NULL;
}


inline void
Container_InitHList (
                     unsigned int                            count,
                     struct container__hash_bucket* restrict buckets,
                     struct container__hlist* restrict       hlist
                    )
{
    Container_InitCList(&hlist->list);
    Container_InitHash(count, buckets, &hlist->hash);
}

inline void
Container_ResetHList (struct container__hlist* restrict hlist)
{
    Container_ResetCList(&hlist->list);
    Container_ResetHash(&hlist->hash);
}

inline struct container__hash_bucket*
Container_LookupHListBucket (unsigned int value_hash, struct container__hlist* restrict hlist)
{
    struct container__hash_bucket* hash_bucket;

    hash_bucket = Container_LookupHashBucket(value_hash, &hlist->hash);

    return hash_bucket;
}

inline struct container__hlist_node*
Container_LookupHListNode (
                           unsigned int                             value_hash,
                           void*                                    value,
                           struct container__hlist* restrict        hlist,
                           container__hlist_lookup_type             lookup,
                           void*                                    user_data,
                           struct container__hash_bucket** restrict searched_bucket
                          )
{
    struct container__hlist_hash_lookup_data hlist_hash_lookup;
    struct container__hash_node*             hash_node;
    struct container__hlist_node*            hlist_node;

    hlist_hash_lookup.user_data = user_data;
    hlist_hash_lookup.lookup    = lookup;

    hash_node = Container_LookupHashNode(
                                         value_hash,
                                         value,
                                         &hlist->hash,
                                         &Container_HListHashLookup,
                                         &hlist_hash_lookup,
                                         searched_bucket
                                        );
    if(hash_node == NULL)
        return NULL;

    hlist_node = CONTAINER__CONTAINER_OF(hash_node, struct container__hlist_node, hash_node);

    return hlist_node;
}

inline void
Container_AddHListNode (
                        unsigned int                           value_hash,
                        struct container__hlist_node* restrict node,
                        struct container__hlist* restrict      hlist
                       )
{
    Container_AddCListHead(&node->list_node, &hlist->list);
    Container_AddHashNode(value_hash, &node->hash_node, &hlist->hash);
}

inline void
Container_InsHListNode (
                        struct container__hlist_node* restrict  node,
                        struct container__hash_bucket* restrict bucket,
                        struct container__hlist* restrict       hlist
                       )
{
    Container_AddCListHead(&node->list_node, &hlist->list);
    Container_InsHashNode(&node->hash_node, bucket);
}

inline void
Container_RemoveHListNode (struct container__hlist_node* restrict node)
{
    Container_RemoveCListNode(&node->list_node);
    Container_RemoveHashNode(&node->hash_node);
}

inline enum container__hlist_state
Container_HListState (struct container__hlist* restrict hlist)
{
    enum container__clist_state state;

    state = Container_CListState(&hlist->list);
    if(state == container__clist_populated)
        return container__hlist_populated;

    return container__hlist_empty;
}

inline void
Container_StartHListBucketScan (
                                struct container__hash_bucket* restrict       bucket,
                                struct container__hlist_bucket_scan* restrict scan
                               )
{
    Container_StartHashBucketScan(bucket, &scan->node_scan);
    Container_UpdateHListBucketScan(scan);
}

inline void
Container_ResumeHListBucketScan (
                                 struct container__hash_bucket* restrict       bucket,
                                 struct container__hlist_bucket_scan* restrict scan
                                )
{
    Container_ResumeHashBucketScan(bucket, &scan->node_scan);
    Container_UpdateHListBucketScan(scan);
}

inline enum container__hlist_bucket_scan_state
Container_HListBucketScanState (struct container__hlist_bucket_scan* restrict scan)
{
    if(scan->current_node == NULL)
        return container__hlist_bucket_scan_finished;

    return container__hlist_bucket_scan_incomplete;
}

inline void
Container_StartHListScanNode (
                              struct container__hlist_node* restrict node,
                              struct container__hlist* restrict      hlist,
                              struct container__hlist_scan* restrict scan
                             )
{
    Container_StartCListScanNode(&node->list_node, &scan->node_scan);
    Container_UpdateHListScan(hlist, scan);
}

inline void
Container_StartHListScanHead (
                              struct container__hlist* restrict      hlist,
                              struct container__hlist_scan* restrict scan
                             )
{
    Container_StartCListScanHead(&hlist->list, &scan->node_scan);
    Container_UpdateHListScan(hlist, scan);
}

inline void
Container_StartHListScanTail (
                              struct container__hlist* restrict      hlist,
                              struct container__hlist_scan* restrict scan
                             )
{
    Container_StartCListScanTail(&hlist->list, &scan->node_scan);
    Container_UpdateHListScan(hlist, scan);
}

inline void
Container_ResumeHListScanNext (
                               struct container__hlist* restrict      hlist,
                               struct container__hlist_scan* restrict scan
                              )
{
    Container_ResumeCListScanNext(&scan->node_scan);
    Container_UpdateHListScan(hlist, scan);
}

inline void
Container_ResumeHListScanPrev (
                               struct container__hlist* restrict      hlist,
                               struct container__hlist_scan* restrict scan
                              )
{
    Container_ResumeCListScanPrev(&scan->node_scan);
    Container_UpdateHListScan(hlist, scan);
}

inline enum container__hlist_scan_state
Container_HListScanState (struct container__hlist_scan* restrict scan)
{
    if(scan->current_node == NULL)
        return container__hlist_scan_finished;

    return container__hlist_scan_incomplete;
}


#endif
