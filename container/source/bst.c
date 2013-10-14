#include <container/bst.h>


extern void
Container_InitBST (struct container__bst* restrict);

extern void
Container_ResetBST (struct container__bst* restrict);


extern enum container__error_code
Container_LookupBSTNode (
                         void*,
                         struct container__bst* restrict,
                         container__bst_lookup_type,
                         void*,
                         struct container__bst_node** restrict
                        );


extern void
Container_AddBSTNode (
                      struct container__bst_node* restrict,
                      struct container__bst* restrict,
                      container__bst_compare_type,
                      void*
                     );

extern void
Container_InsertBSTNode (
                         struct container__bst_node* restrict,
                         struct container__bst_node* restrict,
                         container__bst_compare_type,
                         void*
                        );

extern void
Container_RemoveBSTNode (
                         struct container__bst_node* restrict,
                         struct container__bst* restrict
                        );


extern enum container__bst_state
Container_BSTState (struct container__bst* restrict);


extern void
Container_StartBSTScanNode (
                            struct container__bst_node* restrict,
                            struct container__bst* restrict,
                            struct container__bst_scan* restrict
                           );

extern void
Container_StartBSTScanLeft (
                            struct container__bst* restrict,
                            struct container__bst_scan* restrict
                           );

extern void
Container_StartBSTScanRight (
                             struct container__bst* restrict,
                             struct container__bst_scan* restrict
                            );

extern void
Container_ResumeBSTScanLeft (
                             struct container__bst* restrict,
                             struct container__bst_scan* restrict
                            );

extern void
Container_ResumeBSTScanRight (
                              struct container__bst* restrict,
                              struct container__bst_scan* restrict
                             );

extern enum container__bst_scan_state
Container_BSTScanState (struct container__bst_scan* restrict);


extern void
Container_UpdateBSTScan (
                         struct container__bst* restrict,
                         struct container__bst_scan* restrict
                        );
