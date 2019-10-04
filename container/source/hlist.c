#include <container/hlist.h>


extern void
Container_InitHList (
                     unsigned int,
                     struct container__hash_bucket* restrict,
                     struct container__hlist* restrict
                    );

extern void
Container_ResetHList (struct container__hlist* restrict);


extern struct container__hash_bucket*
Container_LookupHListBucket (unsigned int, struct container__hlist* restrict);

extern struct container__hlist_node*
Container_LookupHListNode (
                           unsigned int,
                           void*,
                           struct container__hlist* restrict,
                           container__hlist_lookup_type,
                           void*,
                           struct container__hash_bucket** restrict
                          );


extern void
Container_AddHListNode (
                        unsigned int,
                        struct container__hlist_node* restrict,
                        struct container__hlist* restrict
                       );

extern void
Container_InsHListNode (
                        struct container__hlist_node* restrict,
                        struct container__hash_bucket* restrict,
                        struct container__hlist* restrict
                       );

extern void
Container_RemoveHListNode (struct container__hlist_node* restrict);


extern enum container__hlist_state
Container_HListState (struct container__hlist* restrict);


extern void
Container_StartHListBucketScan (
                                struct container__hash_bucket* restrict,
                                struct container__hlist_bucket_scan* restrict
                               );

extern void
Container_ResumeHListBucketScan (
                                 struct container__hash_bucket* restrict,
                                 struct container__hlist_bucket_scan* restrict
                                );

extern enum container__hlist_bucket_scan_state
Container_HListBucketScanState (struct container__hlist_bucket_scan* restrict);


extern void
Container_StartHListScanNode (
                              struct container__hlist_node* restrict,
                              struct container__hlist* restrict,
                              struct container__hlist_scan* restrict
                             );

extern void
Container_StartHListScanHead (
                              struct container__hlist* restrict,
                              struct container__hlist_scan* restrict
                             );

extern void
Container_StartHListScanTail (
                              struct container__hlist* restrict,
                              struct container__hlist_scan* restrict
                             );

extern void
Container_ResumeHListScanNext (
                               struct container__hlist* restrict,
                               struct container__hlist_scan* restrict
                              );

extern void
Container_ResumeHListScanPrev (
                               struct container__hlist* restrict,
                               struct container__hlist_scan* restrict
                              );

extern enum container__hlist_scan_state
Container_HListScanState (struct container__hlist_scan* restrict);


extern enum container__hash_cmp_result
Container_HListHashLookup (void*, struct container__hash_node* restrict, void*);


extern void
Container_UpdateHListBucketScan (struct container__hlist_bucket_scan* restrict);

extern void
Container_UpdateHListScan (
                           struct container__hlist* restrict,
                           struct container__hlist_scan* restrict
                          );
