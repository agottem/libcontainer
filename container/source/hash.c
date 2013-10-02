#include <container/hash.h>


extern void
Container_InitHash (
                    unsigned int,
                    struct container__hash_bucket* restrict,
                    struct container__hash* restrict
                   );

extern void
Container_ResetHash (struct container__hash* restrict);


extern void
Container_AddHashNode (
                       unsigned int,
                       struct container__hash_node* restrict,
                       struct container__hash* restrict
                      );

extern void
Container_InsertHashNode (
                          struct container__hash_node* restrict,
                          struct container__hash_bucket* restrict
                         );

extern void
Container_RemoveHashNode (struct container__hash_node* restrict);


extern struct container__hash_node*
Container_LookupHashNode (
                          unsigned int,
                          void*,
                          struct container__hash* restrict,
                          container__hash_lookup_type,
                          void*,
                          struct container__hash_bucket** restrict
                         );


extern enum container__hash_bucket_state
Container_HashBucketState (struct container__hash_bucket* restrict);


extern void
Container_StartHashBucketScan (
                               struct container__hash_bucket_scan* restrict,
                               struct container__hash_bucket* restrict
                              );

extern void
Container_ResumeHashBucketScan (
                                struct container__hash_bucket_scan* restrict,
                                struct container__hash_bucket* restrict
                               );

extern enum container__hash_bucket_scan_state
Container_HashBucketScanState (struct container__hash_bucket_scan* restrict);


extern void
Container_UpdateHashBucketScan (
                                struct container__hash_bucket_scan* restrict,
                                struct container__hash_bucket* restrict
                               );
