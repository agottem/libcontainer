#include <container/bal.h>


extern void
Container_InitBal (
                   size_t,
                   struct container__bal_bucket* restrict,
                   struct container__bal* restrict
                  );

extern void
Container_ResetBal (struct container__bal* restrict);


extern void
Container_MergeBal (struct container__bal* restrict, struct container__bal* restrict);


extern void
Container_AddBalNode (
                      struct container__bal_node* restrict,
                      struct container__bal* restrict
                     );

extern void
Container_RemoveBalNode (
                         struct container__bal_node* restrict,
                         struct container__bal* restrict
                        );


extern enum container__bal_bucket_state
Container_BalBucketState (struct container__bal_bucket* restrict);


extern void
Container_StartBalScanLight (
                             struct container__bal_scan* restrict,
                             struct container__bal* restrict
                            );

extern void
Container_StartBalScanHeavy (
                             struct container__bal_scan* restrict,
                             struct container__bal* restrict
                            );

extern void
Container_ResumeBalScanLight (
                              struct container__bal_scan* restrict,
                              struct container__bal* restrict
                             );

extern void
Container_ResumeBalScanHeavy (
                              struct container__bal_scan* restrict,
                              struct container__bal* restrict
                             );

extern enum container__bal_scan_state
Container_BalScanState (
                        struct container__bal_scan* restrict,
                        struct container__bal* restrict
                       );


extern void
Container_StartBalBucketScan (
                              struct container__bal_bucket_scan* restrict,
                              struct container__bal_bucket* restrict
                             );

extern void
Container_ResumeBalBucketScan (
                               struct container__bal_bucket_scan* restrict,
                               struct container__bal_bucket* restrict
                              );

extern enum container__bal_bucket_scan_state
Container_BalBucketScanState (
                              struct container__bal_bucket_scan* restrict,
                              struct container__bal_bucket* restrict
                             );


extern void
Container_UpdateBalScan (struct container__bal_scan* restrict);

extern void
Container_UpdateBalBucketScan (
                               struct container__bal_bucket_scan* restrict,
                               struct container__bal_bucket* restrict
                              );
