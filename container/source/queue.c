#include <container/queue.h>


extern void
Container_InitQueue (struct container__queue* restrict);

extern void
Container_ResetQueue (struct container__queue* restrict);


extern void
Container_MergeQueueHead (
                          struct container__queue* restrict,
                          struct container__queue* restrict
                         );

extern void
Container_MergeQueueTail (
                          struct container__queue* restrict,
                          struct container__queue* restrict
                         );


extern void
Container_AddQueueHead (
                        struct container__queue_node* restrict,
                        struct container__queue* restrict
                       );

extern void
Container_RemoveQueueHead (struct container__queue* restrict);

extern void
Container_AddQueueTail (
                        struct container__queue_node* restrict,
                        struct container__queue* restrict
                       );


extern enum container__queue_state
Container_QueueState (struct container__queue* restrict);


extern void
Container_StartQueueScan (
                          struct container__queue_scan* restrict,
                          struct container__queue* restrict
                         );

extern void
Container_ResumeQueueScan (struct container__queue_scan* restrict);

extern enum container__queue_scan_state
Container_QueueScanState (struct container__queue_scan* restrict);
