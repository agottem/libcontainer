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
    The hash container manages a hash of elements
 */


#ifndef _CONTAINER__HASH_H_
#define _CONTAINER__HASH_H_


#include <container/error.h>
#include <container/clist.h>


/*
    Valid values a hash lookup function may return
 */
enum container__hash_cmp_result
{
    container__hash_node_not_equal,
    container__hash_node_equal
};

/*
    Valid states for a hash bucket
 */
enum container__hash_bucket_state
{
    container__hash_bucket_populated,
    container__hash_bucket_empty
};

/*
    Valid states for a scan of a hash bucket
 */
enum container__hash_bucket_scan_state
{
    container__hash_bucket_scan_incomplete,
    container__hash_bucket_scan_finished
};


/*
    The node data to be placed in each hash element
 */
struct container__hash_node
{
    struct container__clist_node node;
};

/*
    The buckets which make up the hash container
 */
struct container__hash_bucket
{
    struct container__clist node_list;
};

/*
    The hash container itself
 */
struct container__hash
{
    unsigned int                   bucket_count;
    struct container__hash_bucket* buckets;
};

/*
    The scan structure used to scan an individual hash bucket

    Accessible members:
        current_node -- the current element node being visited
 */
struct container__hash_bucket_scan
{
    struct container__hash_node* current_node;

    struct container__clist_scan node_scan;
};


/*
    The required type for a user-defined hash lookup function.

    For example:
        enum container__hash_cmp_result
        MyLookup (
                  void*                                 id_to_lookup,
                  struct container__hash_node* restrict cmp_node,
                  void*                                 user_data
                 )
        {
            struct my_element* element;

            element = CONTAINER__CONTAINER_OF(cmp_node, struct my_element, node);

            if(element->my_id == *(my_id_type*)id_to_lookup)
                return container__hash_node_equal;

            return container__hash_node_not_equal;
        }
 */
typedef enum container__hash_cmp_result
(*container__hash_lookup_type ) (
                                 void*,
                                 struct container__hash_node* restrict,
                                 void*
                                );


/*
     Initialize a hash.  The container will be empty upon initialization

     Syntax:
         Container_InitHash(bucket_count, my_buckets_array, &my_hash);
 */
inline void
Container_InitHash (
                    unsigned int,
                    struct container__hash_bucket* restrict,
                    struct container__hash* restrict
                   );

/*
     Allocate hash buckets and initialize a hash.  The container will be empty upon
     initialization

     Syntax:
         Container_CreateHash(bucket_count, &my_hash);
 */
inline enum container__error_code
Container_CreateHash (unsigned int, struct container__hash* restrict);

/*
     Cleanup a previously created hash

     Syntax:
         Container_DestroyHash(&my_hash);
 */
inline void
Container_DestroyHash (struct container__hash* restrict);


/*
    Reset a hash container to the initialized state

    Syntax:
        Container_ResetHash(&my_hash);
 */
inline void
Container_ResetHash (struct container__hash* restrict);


/*
   Lookup the bucket which maps to the specified hash value

   Syntax:
     found_bucket = Container_LookupHashBucket(value, &my_hash);
 */
inline struct container__hash_bucket*
Container_LookupHashBucket (unsigned int, struct container__hash* restrict);

/*
    Lookup a node in the hash.  Upon completion, the bucket searched for the node will be
    set and the found node returned.  If no node was found, NULL is returned

    Syntax:
        found_node = Container_LookupHashNode(
                                              MyHashValue(lookup_id),
                                              &lookup_id,
                                              &my_hash,
                                              &MyLookup,
                                              my_user_data,
                                              &searched_bucket
                                             );
 */
inline struct container__hash_node*
Container_LookupHashNode (
                          unsigned int,
                          void*,
                          struct container__hash* restrict,
                          container__hash_lookup_type,
                          void*,
                          struct container__hash_bucket** restrict
                         );


/*
     Add a node to the hash, specifying the hash value for the node

     Syntax:
         Container_AddHashNode(MyHashValue(my_element.my_id), &my_element.node, &my_hash);
 */
inline void
Container_AddHashNode (
                       unsigned int,
                       struct container__hash_node* restrict,
                       struct container__hash* restrict
                      );

/*
    Insert a node into the specified hash bucket

    Syntax:
        Container_InsHashNode(&my_element.node, &my_hash_bucket);
 */
inline void
Container_InsHashNode (
                       struct container__hash_node* restrict,
                       struct container__hash_bucket* restrict
                      );

/*
    Remove a node from the hash

    Syntax:
        Container_RemoveHashNode(&my_element.node);
 */
inline void
Container_RemoveHashNode (struct container__hash_node* restrict);


/*
    Start a scan of a particular hash bucket

    Syntax:
        Container_StartHashBucketScan(&my_buckets[scan_bucket_index], &bucket_scan);
 */
inline void
Container_StartHashBucketScan (
                               struct container__hash_bucket* restrict,
                               struct container__hash_bucket_scan* restrict
                              );


/*
    Resume a scan of a hash bucket

    Syntax:
        Container_ResumeHashBucketScan(&my_buckets[scan_bucket_index], &bucket_scan);
 */
inline void
Container_ResumeHashBucketScan (
                                struct container__hash_bucket* restrict,
                                struct container__hash_bucket_scan* restrict
                               );

/*
    Return the state of a bucket scan

    Syntax:
        scan_state = Container_HashBucketScanState(&bucket_scan);
 */
inline enum container__hash_bucket_scan_state
Container_HashBucketScanState (struct container__hash_bucket_scan* restrict);


#include <container/utils.h>

#include <stddef.h>
#include <stdlib.h>


inline void
Container_UpdateHashBucketScan (
                                struct container__hash_bucket* restrict,
                                struct container__hash_bucket_scan* restrict
                               );


inline void
Container_UpdateHashBucketScan (
                                struct container__hash_bucket* restrict      bucket,
                                struct container__hash_bucket_scan* restrict scan
                               )
{
    enum container__clist_scan_state state;

    state = Container_CListScanState(&bucket->node_list, &scan->node_scan);
    if(state == container__clist_scan_incomplete)
    {
        scan->current_node = CONTAINER__CONTAINER_OF(
                                                     scan->node_scan.current_node,
                                                     struct container__hash_node,
                                                     node
                                                    );
    }
    else
        scan->current_node = NULL;
}


inline void
Container_InitHash (
                    unsigned int                            count,
                    struct container__hash_bucket* restrict buckets,
                    struct container__hash* restrict        hash
                   )
{
    hash->bucket_count = count;
    hash->buckets      = buckets;

    while(count-- > 0)
        Container_InitCList(&buckets[count].node_list);
}

inline enum container__error_code
Container_CreateHash (unsigned int count, struct container__hash* restrict hash)
{
    struct container__hash_bucket* buckets;
    size_t                         alloc_size;

    alloc_size = sizeof(struct container__hash_bucket)*count;
    buckets    = malloc(alloc_size);
    if(buckets == NULL)
        return container__error_memory_alloc;

    Container_InitHash(count, buckets, hash);

    return container__error_none;
}

inline void
Container_DestroyHash (struct container__hash* restrict hash)
{
    free(hash->buckets);
}

inline void
Container_ResetHash (struct container__hash* restrict hash)
{

    struct container__hash_bucket* buckets;
    unsigned int                   count;

    buckets = hash->buckets;
    count   = hash->bucket_count;

    while(count-- > 0)
        Container_ResetCList(&buckets[count].node_list);
}

inline struct container__hash_bucket*
Container_LookupHashBucket (unsigned int value_hash, struct container__hash* restrict hash)
{
    struct container__hash_bucket* hash_bucket;

    value_hash %= hash->bucket_count;

    hash_bucket = &hash->buckets[value_hash];

    return hash_bucket;
}

inline struct container__hash_node*
Container_LookupHashNode (
                          unsigned int                             value_hash,
                          void*                                    value,
                          struct container__hash* restrict         hash,
                          container__hash_lookup_type              lookup,
                          void*                                    user_data,
                          struct container__hash_bucket** restrict searched_bucket
                         )
{
    struct container__hash_bucket_scan scan;
    struct container__hash_bucket*     hash_bucket;

    value_hash %= hash->bucket_count;

    hash_bucket      = &hash->buckets[value_hash];
    *searched_bucket = hash_bucket;

    for(
        Container_StartHashBucketScan(hash_bucket, &scan);
        Container_HashBucketScanState(&scan) != container__hash_bucket_scan_finished;
        Container_ResumeHashBucketScan(hash_bucket, &scan)
       )
    {
        enum container__hash_cmp_result result;

        result = (*lookup)(value, scan.current_node, user_data);
        if(result == container__hash_node_equal)
            return scan.current_node;
    }

    return NULL;
}

inline void
Container_AddHashNode (
                       unsigned int                            value_hash,
                       struct container__hash_node* restrict   node,
                       struct container__hash* restrict        hash
                      )
{
    struct container__hash_bucket* hash_bucket;

    hash_bucket = Container_LookupHashBucket(value_hash, hash);

    Container_AddCListHead(&node->node, &hash_bucket->node_list);
}

inline void
Container_InsHashNode (
                       struct container__hash_node* restrict   node,
                       struct container__hash_bucket* restrict bucket
                      )
{
    Container_AddCListHead(&node->node, &bucket->node_list);
}

inline void
Container_RemoveHashNode (struct container__hash_node* restrict node)
{
    Container_RemoveCListNode(&node->node);
}

inline enum container__hash_bucket_state
Container_HashBucketState (struct container__hash_bucket* restrict bucket)
{
    enum container__clist_state state;

    state = Container_CListState(&bucket->node_list);
    if(state == container__clist_populated)
        return container__hash_bucket_populated;

    return container__hash_bucket_empty;
}

inline void
Container_StartHashBucketScan (
                               struct container__hash_bucket* restrict      bucket,
                               struct container__hash_bucket_scan* restrict scan
                              )
{
    Container_StartCListScanHead(&bucket->node_list, &scan->node_scan);
    Container_UpdateHashBucketScan(bucket, scan);
}

inline void
Container_ResumeHashBucketScan (
                                struct container__hash_bucket* restrict      bucket,
                                struct container__hash_bucket_scan* restrict scan
                               )
{
    Container_ResumeCListScanNext(&scan->node_scan);
    Container_UpdateHashBucketScan(bucket, scan);
}

inline enum container__hash_bucket_scan_state
Container_HashBucketScanState (struct container__hash_bucket_scan* restrict scan)
{
    if(scan->current_node == NULL)
        return container__hash_bucket_scan_finished;

    return container__hash_bucket_scan_incomplete;
}


#endif
