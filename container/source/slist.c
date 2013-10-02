#include <container/slist.h>


extern void
Container_InitSList (struct container__slist* restrict);

extern void
Container_ResetSList (struct container__slist* restrict);


extern void
Container_AddSListHead (
                        struct container__slist_node* restrict,
                        struct container__slist* restrict
                       );

extern void
Container_RemoveSListHead (struct container__slist* restrict);


extern enum container__slist_state
Container_SListState (struct container__slist* restrict);


extern void
Container_StartSListScan (
                          struct container__slist_scan* restrict,
                          struct container__slist* restrict
                         );

extern void
Container_ResumeSListScan (struct container__slist_scan* restrict);

extern enum container__slist_scan_state
Container_SListScanState (struct container__slist_scan* restrict);
