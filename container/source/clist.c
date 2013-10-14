#include <container/clist.h>


extern void
Container_InitCList (struct container__clist* restrict);

extern void
Container_ResetCList (struct container__clist* restrict);


extern void
Container_MergeCListHead (
                          struct container__clist* restrict,
                          struct container__clist* restrict
                         );

extern void
Container_MergeCListTail (
                          struct container__clist* restrict,
                          struct container__clist* restrict
                         );

extern void
Container_PrependCList (
                        struct container__clist_node* restrict,
                        struct container__clist* restrict
                       );

extern void
Container_AppendCList (
                       struct container__clist_node* restrict,
                       struct container__clist* restrict
                      );

extern void
Container_SplitCListBefore (
                            struct container__clist_node* restrict,
                            struct container__clist* restrict,
                            struct container__clist* restrict
                           );

extern void
Container_SplitCListAfter (
                           struct container__clist_node* restrict,
                           struct container__clist* restrict,
                           struct container__clist* restrict
                          );


extern void
Container_AddCListHead (
                        struct container__clist_node* restrict,
                        struct container__clist* restrict
                       );

extern void
Container_RemoveCListHead (struct container__clist* restrict);

extern void
Container_AddCListTail (
                        struct container__clist_node* restrict,
                        struct container__clist* restrict
                       );

extern void
Container_RemoveCListTail (struct container__clist* restrict);

extern void
Container_PrependCListNode (
                            struct container__clist_node* restrict,
                            struct container__clist_node* restrict
                           );

extern void
Container_AppendCListNode (
                           struct container__clist_node* restrict,
                           struct container__clist_node* restrict
                          );

extern void
Container_RemoveCListNode (struct container__clist_node* restrict);


extern enum container__clist_state
Container_CListState (struct container__clist* restrict);


extern void
Container_StartCListScanNode (
                              struct container__clist_node* restrict,
                              struct container__clist_scan* restrict
                             );

extern void
Container_StartCListScanHead (
                              struct container__clist* restrict,
                              struct container__clist_scan* restrict
                             );

extern void
Container_StartCListScanTail (
                              struct container__clist* restrict,
                              struct container__clist_scan* restrict
                             );

extern void
Container_ResumeCListScanNext (struct container__clist_scan* restrict);

extern void
Container_ResumeCListScanPrev (struct container__clist_scan* restrict);

extern enum container__clist_scan_state
Container_CListScanState (
                          struct container__clist* restrict,
                          struct container__clist_scan* restrict
                         );
