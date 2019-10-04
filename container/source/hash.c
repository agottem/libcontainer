#include <container/hash.h>


extern void
Container_InitHash (
                    unsigned int,
                    struct container__hash_bucket* restrict,
                    struct container__hash* restrict
                   );

extern enum container__error_code
Container_CreateHash (unsigned int, struct container__hash* restrict);

extern void
Container_DestroyHash (struct container__hash* restrict);

extern void
Container_ResetHash (struct container__hash* restrict);


extern struct container__hash_bucket*
Container_LookupHashBucket (
                            unsigned int,
                            struct container__hash* restrict
                           );

extern struct container__hash_node*
Container_LookupHashNode (
                          unsigned int,
                          void*,
                          struct container__hash* restrict,
                          container__hash_lookup_type,
                          void*,
                          struct container__hash_bucket** restrict
                         );


extern void
Container_AddHashNode (
                       unsigned int,
                       struct container__hash_node* restrict,
                       struct container__hash* restrict
                      );

extern void
Container_InsHashNode (
                       struct container__hash_node* restrict,
                       struct container__hash_bucket* restrict
                      );

extern void
Container_RemoveHashNode (struct container__hash_node* restrict);


extern enum container__hash_bucket_state
Container_HashBucketState (struct container__hash_bucket* restrict);


extern void
Container_StartHashBucketScan (
                               struct container__hash_bucket* restrict,
                               struct container__hash_bucket_scan* restrict
                              );

extern void
Container_ResumeHashBucketScan (
                                struct container__hash_bucket* restrict,
                                struct container__hash_bucket_scan* restrict
                               );

extern enum container__hash_bucket_scan_state
Container_HashBucketScanState (struct container__hash_bucket_scan* restrict);


extern void
Container_UpdateHashBucketScan (
                                struct container__hash_bucket* restrict,
                                struct container__hash_bucket_scan* restrict
                               );
