#include <container/stdhlist.h>


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
