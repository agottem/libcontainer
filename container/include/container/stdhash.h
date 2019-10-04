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
    Standard types for use with the hash container
 */


#ifndef _CONTAINER__STDHASH_H_
#define _CONTAINER__STDHASH_H_


#include <container/hash.h>


struct container__int_hash_node
{
    int                         value;
    struct container__hash_node node;
};

struct container__uint_hash_node
{
    unsigned int                value;
    struct container__hash_node node;
};

struct container__long_hash_node
{
    long long                   value;
    struct container__hash_node node;
};

struct container__ulong_hash_node
{
    unsigned long long          value;
    struct container__hash_node node;
};

struct container__string_hash_node
{
    char*                       value;
    struct container__hash_node node;
};


inline enum container__hash_cmp_result
Container_IntHashTest (int, int);

inline enum container__hash_cmp_result
Container_IntHashLookup (
                         void*,
                         struct container__hash_node* restrict,
                         void*
                        );

inline void
Container_AddIntHash (
                      int,
                      unsigned int,
                      struct container__int_hash_node* restrict,
                      struct container__hash* restrict
                     );

inline void
Container_InsIntHash (
                      int,
                      struct container__int_hash_node* restrict,
                      struct container__hash_bucket* restrict
                     );

inline enum container__hash_cmp_result
Container_UIntHashTest (unsigned int, unsigned int);

inline enum container__hash_cmp_result
Container_UIntHashLookup (
                          void*,
                          struct container__hash_node* restrict,
                          void*
                         );

inline void
Container_AddUIntHash (
                       unsigned int,
                       unsigned int,
                       struct container__uint_hash_node* restrict,
                       struct container__hash* restrict
                      );

inline void
Container_InsUIntHash (
                       unsigned int,
                       struct container__uint_hash_node* restrict,
                       struct container__hash_bucket* restrict
                      );

inline enum container__hash_cmp_result
Container_LongHashTest (long long, long long);

inline enum container__hash_cmp_result
Container_LongHashLookup (
                          void*,
                          struct container__hash_node* restrict,
                          void*
                         );

inline void
Container_AddLongHash (
                       long long,
                       unsigned int,
                       struct container__long_hash_node* restrict,
                       struct container__hash* restrict
                      );

inline void
Container_InsLongHash (
                       long long,
                       struct container__long_hash_node* restrict,
                       struct container__hash_bucket* restrict
                      );

inline enum container__hash_cmp_result
Container_ULongHashTest (unsigned long long, unsigned long long);

inline enum container__hash_cmp_result
Container_ULongHashLookup (
                           void*,
                           struct container__hash_node* restrict,
                           void*
                          );

inline void
Container_AddULongHash (
                        unsigned long long,
                        unsigned int,
                        struct container__ulong_hash_node* restrict,
                        struct container__hash* restrict
                       );

inline void
Container_InsULongHash (
                        unsigned long long,
                        struct container__ulong_hash_node* restrict,
                        struct container__hash_bucket* restrict
                       );

inline enum container__hash_cmp_result
Container_StringHashTest (char*, char*);

inline enum container__hash_cmp_result
Container_StringHashLookup (
                            void*,
                            struct container__hash_node* restrict,
                            void*
                           );

inline void
Container_AddStringHash (
                         char*,
                         unsigned int,
                         struct container__string_hash_node* restrict,
                         struct container__hash* restrict
                        );

inline void
Container_InsStringHash (
                         char*,
                         struct container__string_hash_node* restrict,
                         struct container__hash_bucket* restrict
                        );


#include <string.h>
#include <container/utils.h>


inline enum container__hash_cmp_result
Container_IntHashTest (int l_value, int r_value)
{
    if(l_value == r_value)
        return container__hash_node_equal;

    return container__hash_node_not_equal;
}

inline enum container__hash_cmp_result
Container_IntHashLookup (
                         void*                                 lookup_value,
                         struct container__hash_node* restrict existing_node,
                         void*                                 user_data
                        )
{
    int* restrict                             int_lookup_value;
    struct container__int_hash_node* restrict existing_int_node;
    enum container__hash_cmp_result           cmp_result;

    int_lookup_value  = lookup_value;
    existing_int_node = CONTAINER__CONTAINER_OF(
                                                existing_node,
                                                struct container__int_hash_node,
                                                node
                                               );

    cmp_result = Container_IntHashTest(*int_lookup_value, existing_int_node->value);

    return cmp_result;
}

inline void
Container_AddIntHash (
                      int                                       value,
                      unsigned int                              value_hash,
                      struct container__int_hash_node* restrict node,
                      struct container__hash* restrict          hash
                     )
{
    node->value = value;

    Container_AddHashNode(
                          value_hash,
                          &node->node,
                          hash
                         );
}

inline void
Container_InsIntHash (
                      int                                       value,
                      struct container__int_hash_node* restrict node,
                      struct container__hash_bucket* restrict   bucket
                     )
{
    node->value = value;

    Container_InsHashNode(&node->node, bucket);
}

inline enum container__hash_cmp_result
Container_UIntHashTest (unsigned int l_value, unsigned int r_value)
{
    if(l_value == r_value)
        return container__hash_node_equal;

    return container__hash_node_not_equal;
}

inline enum container__hash_cmp_result
Container_UIntHashLookup (
                          void*                                 lookup_value,
                          struct container__hash_node* restrict existing_node,
                          void*                                 user_data
                         )
{
    unsigned int* restrict                     uint_lookup_value;
    struct container__uint_hash_node* restrict existing_uint_node;
    enum container__hash_cmp_result            cmp_result;

    uint_lookup_value  = lookup_value;
    existing_uint_node = CONTAINER__CONTAINER_OF(
                                                 existing_node,
                                                 struct container__uint_hash_node,
                                                 node
                                                );

    cmp_result = Container_UIntHashTest(*uint_lookup_value, existing_uint_node->value);

    return cmp_result;
}

inline void
Container_AddUIntHash (
                       unsigned int                               value,
                       unsigned int                               value_hash,
                       struct container__uint_hash_node* restrict node,
                       struct container__hash* restrict           hash
                      )
{
    node->value = value;

    Container_AddHashNode(
                          value_hash,
                          &node->node,
                          hash
                         );
}

inline void
Container_InsUIntHash (
                       unsigned int                               value,
                       struct container__uint_hash_node* restrict node,
                       struct container__hash_bucket* restrict    bucket
                      )
{
    node->value = value;

    Container_InsHashNode(&node->node, bucket);
}

inline enum container__hash_cmp_result
Container_LongHashTest (long long l_value, long long r_value)
{
    if(l_value == r_value)
        return container__hash_node_equal;

    return container__hash_node_not_equal;
}

inline enum container__hash_cmp_result
Container_LongHashLookup (
                          void*                                 lookup_value,
                          struct container__hash_node* restrict existing_node,
                          void*                                 user_data
                         )
{
    long long* restrict                        long_lookup_value;
    struct container__long_hash_node* restrict existing_long_node;
    enum container__hash_cmp_result            cmp_result;

    long_lookup_value  = lookup_value;
    existing_long_node = CONTAINER__CONTAINER_OF(
                                                 existing_node,
                                                 struct container__long_hash_node,
                                                 node
                                                );

    cmp_result = Container_LongHashTest(*long_lookup_value, existing_long_node->value);

    return cmp_result;
}

inline void
Container_AddLongHash (
                       long long                                  value,
                       unsigned int                               value_hash,
                       struct container__long_hash_node* restrict node,
                       struct container__hash* restrict           hash
                      )
{
    node->value = value;

    Container_AddHashNode(
                          value_hash,
                          &node->node,
                          hash
                         );
}

inline void
Container_InsLongHash (
                       long long                                  value,
                       struct container__long_hash_node* restrict node,
                       struct container__hash_bucket* restrict    bucket
                      )
{
    node->value = value;

    Container_InsHashNode(&node->node, bucket);
}

inline enum container__hash_cmp_result
Container_ULongHashTest (unsigned long long l_value, unsigned long long r_value)
{
    if(l_value == r_value)
        return container__hash_node_equal;

    return container__hash_node_not_equal;
}

inline enum container__hash_cmp_result
Container_ULongHashLookup (
                           void*                                 lookup_value,
                           struct container__hash_node* restrict existing_node,
                           void*                                 user_data
                          )
{
    unsigned long long* restrict                ulong_lookup_value;
    struct container__ulong_hash_node* restrict existing_ulong_node;
    enum container__hash_cmp_result             cmp_result;

    ulong_lookup_value  = lookup_value;
    existing_ulong_node = CONTAINER__CONTAINER_OF(
                                                  existing_node,
                                                  struct container__ulong_hash_node,
                                                  node
                                                 );

    cmp_result = Container_ULongHashTest(*ulong_lookup_value, existing_ulong_node->value);

    return cmp_result;
}

inline void
Container_AddULongHash (
                        unsigned long long                          value,
                        unsigned int                                value_hash,
                        struct container__ulong_hash_node* restrict node,
                        struct container__hash* restrict            hash
                       )
{
    node->value = value;

    Container_AddHashNode(
                          value_hash,
                          &node->node,
                          hash
                         );
}

inline void
Container_InsULongHash (
                        unsigned long long                          value,
                        struct container__ulong_hash_node* restrict node,
                        struct container__hash_bucket* restrict     bucket
                       )
{
    node->value = value;

    Container_InsHashNode(&node->node, bucket);
}

inline enum container__hash_cmp_result
Container_StringHashTest (char* l_value, char* r_value)
{
    int delta;

    delta = strcmp(l_value, r_value);
    if(delta == 0)
        return container__hash_node_equal;

    return container__hash_node_not_equal;
}

inline enum container__hash_cmp_result
Container_StringHashLookup (
                            void*                                 lookup_value,
                            struct container__hash_node* restrict existing_node,
                            void*                                 user_data
                           )
{
    struct container__string_hash_node* restrict existing_string_node;
    enum container__hash_cmp_result          cmp_result;

    existing_string_node = CONTAINER__CONTAINER_OF(
                                                   existing_node,
                                                   struct container__string_hash_node,
                                                   node
                                                  );

    cmp_result = Container_StringHashTest(lookup_value, existing_string_node->value);

    return cmp_result;
}

inline void
Container_AddStringHash (
                         char* restrict                               value,
                         unsigned int                                 value_hash,
                         struct container__string_hash_node* restrict node,
                         struct container__hash* restrict             hash
                        )
{
    node->value = value;

    Container_AddHashNode(
                          value_hash,
                          &node->node,
                          hash
                         );
}

inline void
Container_InsStringHash (
                         char* restrict                               value,
                         struct container__string_hash_node* restrict node,
                         struct container__hash_bucket* restrict      bucket
                        )
{
    node->value = value;

    Container_InsHashNode(&node->node, bucket);
}


#endif
