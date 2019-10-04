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
    Standard types for use with the hlist container
 */


#ifndef _CONTAINER__HLIST_H_
#define _CONTAINER__HLIST_H_


#include <container/sync.h>
#include <container/hlist.h>


struct container__int_hlist_node
{
    int                          value;
    struct container__hlist_node node;
};

struct container__uint_hlist_node
{
    unsigned int                 value;
    struct container__hlist_node node;
};

struct container__long_hlist_node
{
    long long                    value;
    struct container__hlist_node node;
};

struct container__ulong_hlist_node
{
    unsigned long long           value;
    struct container__hlist_node node;
};

struct container__string_hlist_node
{
    char*                        value;
    struct container__hlist_node node;
};


inline enum container__hlist_cmp_result
Container_IntHListTest (int, int);

inline enum container__hlist_cmp_result
Container_IntHListLookup (
                          void*,
                          struct container__hlist_node* restrict,
                          void*
                         );

inline void
Container_AddIntHList (
                       int,
                       unsigned int,
                       struct container__int_hlist_node* restrict,
                       void*,
                       container__lock_sync_type,
                       container__unlock_sync_type,
                       struct container__hlist* restrict
                      );

inline void
Container_InsIntHList (
                       int,
                       struct container__int_hlist_node* restrict,
                       struct container__hash_bucket* restrict,
                       struct container__hlist* restrict
                      );

inline enum container__hlist_cmp_result
Container_UIntHListTest (unsigned int, unsigned int);

inline enum container__hlist_cmp_result
Container_UIntHListLookup (
                           void*,
                           struct container__hlist_node* restrict,
                           void*
                          );

inline void
Container_AddUIntHList (
                        unsigned int,
                        unsigned int,
                        struct container__uint_hlist_node* restrict,
                        void*,
                        container__lock_sync_type,
                        container__unlock_sync_type,
                        struct container__hlist* restrict
                       );

inline void
Container_InsUIntHList (
                        unsigned int,
                        struct container__uint_hlist_node* restrict,
                        struct container__hash_bucket* restrict,
                        struct container__hlist* restrict
                       );


inline enum container__hlist_cmp_result
Container_LongHListTest (long long, long long);

inline enum container__hlist_cmp_result
Container_LongHListLookup (
                           void*,
                           struct container__hlist_node* restrict,
                           void*
                          );

inline void
Container_AddLongHList (
                        long long,
                        unsigned int,
                        struct container__long_hlist_node* restrict,
                        void*,
                        container__lock_sync_type,
                        container__unlock_sync_type,
                        struct container__hlist* restrict
                       );

inline void
Container_InsLongHList (
                        long long,
                        struct container__long_hlist_node* restrict,
                        struct container__hash_bucket* restrict,
                        struct container__hlist* restrict
                       );

inline enum container__hlist_cmp_result
Container_ULongHListTest (unsigned long long, unsigned long long);

inline enum container__hlist_cmp_result
Container_ULongHListLookup (
                            void*,
                            struct container__hlist_node* restrict,
                            void*
                           );

inline void
Container_AddULongHList (
                        unsigned long long,
                        unsigned int,
                        struct container__ulong_hlist_node* restrict,
                        void*,
                        container__lock_sync_type,
                        container__unlock_sync_type,
                        struct container__hlist* restrict
                       );

inline void
Container_InsULongHList (
                         unsigned long long,
                         struct container__ulong_hlist_node* restrict,
                         struct container__hash_bucket* restrict,
                         struct container__hlist* restrict
                        );


inline enum container__hlist_cmp_result
Container_StringHListTest (char*, char*);

inline enum container__hlist_cmp_result
Container_StringHListLookup (
                             void*,
                             struct container__hlist_node* restrict,
                             void*
                            );

inline void
Container_AddStringHList (
                          char*,
                          unsigned int,
                          struct container__string_hlist_node* restrict,
                          void*,
                          container__lock_sync_type,
                          container__unlock_sync_type,
                          struct container__hlist* restrict
                         );

inline void
Container_InsStringHList (
                          char*,
                          struct container__string_hlist_node* restrict,
                          struct container__hash_bucket* restrict,
                          struct container__hlist* restrict
                         );


#include <string.h>


inline enum container__hlist_cmp_result
Container_IntHListTest (int l_value, int r_value)
{
    if(l_value == r_value)
        return container__hlist_node_equal;

    return container__hlist_node_not_equal;
}

inline enum container__hlist_cmp_result
Container_IntHListLookup (
                          void*                                  lookup_value,
                          struct container__hlist_node* restrict existing_node,
                          void*                                  user_data
                         )
{
    int* restrict                              int_lookup_value;
    struct container__int_hlist_node* restrict existing_int_node;
    enum container__hlist_cmp_result           cmp_result;

    int_lookup_value  = lookup_value;
    existing_int_node = CONTAINER__CONTAINER_OF(
                                                existing_node,
                                                struct container__int_hlist_node,
                                                node
                                               );

    cmp_result = Container_IntHListTest(*int_lookup_value, existing_int_node->value);

    return cmp_result;
}

inline void
Container_AddIntHList (
                       int                                        value,
                       unsigned int                               value_hash,
                       struct container__int_hlist_node* restrict node,
                       void*                                      sync,
                       container__lock_sync_type                  lock_sync,
                       container__unlock_sync_type                unlock_sync,
                       struct container__hlist* restrict          hlist
                      )
{
    node->value = value;

    Container_LockSync(sync, lock_sync);

    Container_AddHListNode(
                           value_hash,
                           &node->node,
                           hlist
                          );

    Container_UnlockSync(sync, lock_sync);
}

inline void
Container_InsIntHList (
                       int                                        value,
                       struct container__int_hlist_node* restrict node,
                       struct container__hash_bucket* restrict    bucket,
                       struct container__hlist* restrict          hlist
                      )
{
    node->value = value;

    Container_InsHListNode(&node->node, bucket, hlist);
}

inline enum container__hlist_cmp_result
Container_UIntHListTest (unsigned int l_value, unsigned int r_value)
{
    if(l_value == r_value)
        return container__hlist_node_equal;

    return container__hlist_node_not_equal;
}

inline enum container__hlist_cmp_result
Container_UIntHListLookup (
                           void*                                  lookup_value,
                           struct container__hlist_node* restrict existing_node,
                           void*                                  user_data
                          )
{
    unsigned int* restrict                      uint_lookup_value;
    struct container__uint_hlist_node* restrict existing_uint_node;
    enum container__hlist_cmp_result            cmp_result;

    uint_lookup_value  = lookup_value;
    existing_uint_node = CONTAINER__CONTAINER_OF(
                                                 existing_node,
                                                 struct container__uint_hlist_node,
                                                 node
                                                );

    cmp_result = Container_UIntHListTest(*uint_lookup_value, existing_uint_node->value);

    return cmp_result;
}

inline void
Container_AddUIntHList (
                        unsigned int                                value,
                        unsigned int                                value_hash,
                        struct container__uint_hlist_node* restrict node,
                        void*                                       sync,
                        container__lock_sync_type                   lock_sync,
                        container__unlock_sync_type                 unlock_sync,
                        struct container__hlist* restrict           hlist
                       )
{
    node->value = value;

    Container_LockSync(sync, lock_sync);

    Container_AddHListNode(
                           value_hash,
                           &node->node,
                           hlist
                          );

    Container_UnlockSync(sync, lock_sync);
}

inline void
Container_InsUIntHList (
                       unsigned int                                value,
                       struct container__uint_hlist_node* restrict node,
                       struct container__hash_bucket* restrict     bucket,
                        struct container__hlist* restrict          hlist
                       )
{
    node->value = value;

    Container_InsHListNode(&node->node, bucket, hlist);
}

inline enum container__hlist_cmp_result
Container_LongHListTest (long long l_value, long long r_value)
{
    if(l_value == r_value)
        return container__hlist_node_equal;

    return container__hlist_node_not_equal;
}

inline enum container__hlist_cmp_result
Container_LongHListLookup (
                           void*                                  lookup_value,
                           struct container__hlist_node* restrict existing_node,
                           void*                                  user_data
                          )
{
    long long* restrict                         long_lookup_value;
    struct container__long_hlist_node* restrict existing_long_node;
    enum container__hlist_cmp_result            cmp_result;

    long_lookup_value = lookup_value;
    existing_long_node = CONTAINER__CONTAINER_OF(
                                                 existing_node,
                                                 struct container__long_hlist_node,
                                                 node
                                                );

    cmp_result = Container_LongHListTest(*long_lookup_value, existing_long_node->value);

    return cmp_result;
}

inline void
Container_AddLongHList (
                        long long                                   value,
                        unsigned int                                value_hash,
                        struct container__long_hlist_node* restrict node,
                        void*                                       sync,
                        container__lock_sync_type                   lock_sync,
                        container__unlock_sync_type                 unlock_sync,
                        struct container__hlist* restrict           hlist
                       )
{
    node->value = value;

    Container_LockSync(sync, lock_sync);

    Container_AddHListNode(
                           value_hash,
                           &node->node,
                           hlist
                          );

    Container_UnlockSync(sync, lock_sync);
}

inline void
Container_InsLongHList (
                        long long                                   value,
                        struct container__long_hlist_node* restrict node,
                        struct container__hash_bucket* restrict     bucket,
                        struct container__hlist* restrict           hlist
                       )
{
    node->value = value;

    Container_InsHListNode(&node->node, bucket, hlist);
}

inline enum container__hlist_cmp_result
Container_ULongHListTest (unsigned long long l_value, unsigned long long r_value)
{
    if(l_value == r_value)
        return container__hlist_node_equal;

    return container__hlist_node_not_equal;
}

inline enum container__hlist_cmp_result
Container_ULongHListLookup (
                            void*                                  lookup_value,
                            struct container__hlist_node* restrict existing_node,
                            void*                                  user_data
                           )
{
    unsigned long long* restrict                 ulong_lookup_value;
    struct container__ulong_hlist_node* restrict existing_ulong_node;
    enum container__hlist_cmp_result             cmp_result;

    ulong_lookup_value = lookup_value;
    existing_ulong_node  = CONTAINER__CONTAINER_OF(
                                                   existing_node,
                                                   struct container__ulong_hlist_node,
                                                   node
                                                  );

    cmp_result = Container_ULongHListTest(*ulong_lookup_value, existing_ulong_node->value);

    return cmp_result;
}

inline void
Container_AddULongHList (
                         unsigned long long                           value,
                         unsigned int                                 value_hash,
                         struct container__ulong_hlist_node* restrict node,
                         void*                                        sync,
                         container__lock_sync_type                    lock_sync,
                         container__unlock_sync_type                  unlock_sync,
                         struct container__hlist* restrict            hlist
                        )
{
    node->value = value;

    Container_LockSync(sync, lock_sync);

    Container_AddHListNode(
                           value_hash,
                           &node->node,
                           hlist
                          );

    Container_UnlockSync(sync, lock_sync);
}

inline void
Container_InsULongHList (
                         unsigned long long                           value,
                         struct container__ulong_hlist_node* restrict node,
                         struct container__hash_bucket* restrict      bucket,
                         struct container__hlist* restrict            hlist
                        )
{
    node->value = value;

    Container_InsHListNode(&node->node, bucket, hlist);
}

inline enum container__hlist_cmp_result
Container_StringHListTest (char* l_value, char* r_value)
{
    int delta;

    delta = strcmp(l_value, r_value);
    if(delta == 0)
        return container__hlist_node_equal;

    return container__hlist_node_not_equal;
}

inline enum container__hlist_cmp_result
Container_StringHListLookup (
                             void*                                  lookup_value,
                             struct container__hlist_node* restrict existing_node,
                             void*                                  user_data
                            )
{
    char* restrict                                string_lookup_value;
    struct container__string_hlist_node* restrict existing_string_node;
    enum container__hlist_cmp_result              cmp_result;

    string_lookup_value  = lookup_value;
    existing_string_node = CONTAINER__CONTAINER_OF(
                                                   existing_node,
                                                   struct container__string_hlist_node,
                                                   node
                                                  );

    cmp_result = Container_StringHListTest(string_lookup_value, existing_string_node->value);

    return cmp_result;
}

inline void
Container_AddStringHList (
                          char*                                         value,
                          unsigned int                                  value_hash,
                          struct container__string_hlist_node* restrict node,
                          void*                                         sync,
                          container__lock_sync_type                     lock_sync,
                          container__unlock_sync_type                   unlock_sync,
                          struct container__hlist* restrict             hlist
                         )
{
    node->value = value;

    Container_LockSync(sync, lock_sync);

    Container_AddHListNode(
                           value_hash,
                           &node->node,
                           hlist
                          );

    Container_UnlockSync(sync, lock_sync);
}

inline void
Container_InsStringHList (
                          char*                                         value,
                          struct container__string_hlist_node* restrict node,
                          struct container__hash_bucket* restrict       bucket,
                          struct container__hlist* restrict             hlist
                         )
{
    node->value = value;

    Container_InsHListNode(&node->node, bucket, hlist);
}


#endif
