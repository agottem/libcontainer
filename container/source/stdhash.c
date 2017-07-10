#include <container/stdhash.h>


extern enum container__hash_compare_result
Container_IntHashTest (int, int);

extern enum container__hash_compare_result
Container_IntHashLookup (
                         void*,
                         struct container__hash_node* restrict,
                         void*
                        );

extern void
Container_AddIntHash (
                      int,
                      unsigned int,
                      struct container__int_hash_node* restrict,
                      struct container__hash* restrict
                     );

extern void
Container_InsertIntHash (
                         int,
                         struct container__int_hash_node* restrict,
                         struct container__hash_bucket* restrict
                        );

extern enum container__hash_compare_result
Container_UIntHashTest (unsigned int, unsigned int);

extern enum container__hash_compare_result
Container_UIntHashLookup (
                          void*,
                          struct container__hash_node* restrict,
                          void*
                         );

extern void
Container_AddUIntHash (
                       unsigned int,
                       unsigned int,
                       struct container__uint_hash_node* restrict,
                       struct container__hash* restrict
                      );

extern void
Container_InsertUIntHash (
                          unsigned int,
                          struct container__uint_hash_node* restrict,
                          struct container__hash_bucket* restrict
                         );

extern enum container__hash_compare_result
Container_LongHashTest (long long, long long);

extern enum container__hash_compare_result
Container_LongHashLookup (
                          void*,
                          struct container__hash_node* restrict,
                          void*
                         );

extern void
Container_AddLongHash (
                       long long,
                       unsigned int,
                       struct container__long_hash_node* restrict,
                       struct container__hash* restrict
                      );

extern void
Container_InsertLongHash (
                          long long,
                          struct container__long_hash_node* restrict,
                          struct container__hash_bucket* restrict
                         );

extern enum container__hash_compare_result
Container_ULongHashTest (unsigned long long, unsigned long long);

extern enum container__hash_compare_result
Container_ULongHashLookup (
                           void*,
                           struct container__hash_node* restrict,
                           void*
                          );

extern void
Container_AddULongHash (
                        unsigned long long,
                        unsigned int,
                        struct container__ulong_hash_node* restrict,
                        struct container__hash* restrict
                       );

extern void
Container_InsertULongHash (
                           unsigned long long,
                           struct container__ulong_hash_node* restrict,
                           struct container__hash_bucket* restrict
                          );

extern enum container__hash_compare_result
Container_StringHashTest (char*, char*);

extern enum container__hash_compare_result
Container_StringHashLookup (
                            void*,
                            struct container__hash_node* restrict,
                            void*
                           );

extern void
Container_AddStringHash (
                         char*,
                         unsigned int,
                         struct container__string_hash_node* restrict,
                         struct container__hash* restrict
                        );

extern void
Container_InsertStringHash (
                            char*,
                            struct container__string_hash_node* restrict,
                            struct container__hash_bucket* restrict
                           );
