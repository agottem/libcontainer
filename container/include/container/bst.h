/*
    The C container library is licensed under the simplified BSD license:

    Copyright 2013, Andrew Gottemoller
    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of
    conditions and the following disclaimer:

    Redistributions in binary form must reproduce the above copyright notice, this list
    of conditions and the following disclaimer in the documentation and/or other materials
    provided with the distribution.

    Neither the name Andrew Gottemoller nor the names of its contributors may be used to
    endorse or promote products derived from this software without specific prior written
    permission.
 */

/*
    The bst container implements a basic binary search tree.  Since balancing is not performed,
    fairly random key values should be stored in this container
 */

#ifndef _CONTAINER__BST_H_
#define _CONTAINER__BST_H_


#include <container/error.h>
#include <container/clist.h>


/*
    Valid values a bst cmp function may return
 */
enum container__bst_cmp_result
{
    container__bst_node_left,
    container__bst_node_right,
    container__bst_node_equal
};

/*
    Valid states for a bst container
 */
enum container__bst_state
{
    container__bst_populated,
    container__bst_empty
};

/*
    Valid states for a scan of a bst
 */
enum container__bst_scan_state
{
    container__bst_scan_incomplete,
    container__bst_scan_finished
};


/*
    The node data to be placed in each hash element
 */
struct container__bst_node
{
    struct container__bst_node* parent;
    struct container__bst_node* left;
    struct container__bst_node* right;

    struct container__clist_node ordering_node;
};

/*
    The bst container itself
 */
struct container__bst
{
    struct container__bst_node* root;

    struct container__clist ordering;
};

/*
    The scan structure used to scan a bst

    Accessible members:
        current_node -- the current element node being visited
 */
struct container__bst_scan
{
    struct container__bst_node* current_node;

    struct container__clist_scan ordering_scan;
};


/*
    The required type for a user-defined bst lookup function.  The lookup function
    is responsible for comparing a value to a node and returning the relative direction
    of traversal

    For example:
        enum container__bst_cmp_result
        MyLookup (
                  void*                                lookup_key,
                  struct container__bst_node* restrict node_ptr,
                  void*                                user_data
                 )
        {
            struct my_element* element;

            element = CONTAINER__CONTAINER_OF(node_ptr, struct my_element, node);

            if(*(my_key_type*)lookup_key < element->my_key)
                return container__bst_node_left;
            else if(*(my_key_type*)lookup_key > element->my_key)
                return container__bst_node_right;

            return container__bst_node_equal;
        }
 */
typedef enum container__bst_cmp_result
(*container__bst_lookup_type ) (
                                void*,
                                struct container__bst_node* restrict,
                                void*
                               );


/*
    The required type for a user-defined bst cmp function.  The cmp function
    is responsible for comparing two nodes and returning relative placement

    For example:
        enum container__bst_cmp_result
        MyCmp (
               struct container__bst_node* restrict node_1,
               struct container__bst_node* restrict node_2,
               void*                                user_data
              )
        {
            struct my_element* element_1;

            element_1 = CONTAINER__CONTAINER_OF(node_1, struct my_element, node);
            element_2 = CONTAINER__CONTAINER_OF(node_2, struct my_element, node);

            if(element_1->my_key < element_2->my_key)
                return container__bst_node_left;
            else if(element_1->my_key > element_2->my_key)
                return container__bst_node_right;

            return container__bst_node_equal;
        }
 */
typedef enum container__bst_cmp_result
(*container__bst_cmp_type) (
                            struct container__bst_node* restrict,
                            struct container__bst_node* restrict,
                            void*
                           );


/*
    Initialize a bst.  The container will be empty upon initialization

    Syntax:
        Container_InitBST(&my_bst);
 */
inline void
Container_InitBST (struct container__bst* restrict);

/*
    Reset a bst container to the initialized state

    Syntax:
        Container_ResetBST(&my_bst);
 */
inline void
Container_ResetBST (struct container__bst* restrict);


/*
    Lookup a node corresponding to the specified value in the bst.  Upon completion, either
    no error will be returned and nearest_found_node will be set to the matching node, or
    an error will be returned and nearest_found_node will be set to the node nearest the specified
    lookup key which can then be used to quickly insert a node with the specified lookup key value

    Syntax:
        error = Container_LookupBSTNode(
                                        &my_lookup_key_value,
                                        &my_bst,
                                        &MyLookup,
                                        user_data,
                                        &nearest_found_node
                                       );
 */
inline enum container__error_code
Container_LookupBSTNode (
                         void*,
                         struct container__bst* restrict,
                         container__bst_lookup_type,
                         void*,
                         struct container__bst_node** restrict
                        );


/*
    Add a node to the bst

    Syntax:
        Container_AddBSTNode(&my_element.node, &my_bst, &MyCmp, user_data);
 */
inline void
Container_AddBSTNode (
                      struct container__bst_node* restrict,
                      struct container__bst* restrict,
                      container__bst_cmp_type,
                      void*
                     );

/*
    Insert a node starting the insertion search from the specified node

    Syntax:
       Container_InsBSTNode(&my_element.node, existing_node_ptr, &MyCmp, user_data);
 */
inline void
Container_InsBSTNode (
                      struct container__bst_node* restrict,
                      struct container__bst_node* restrict,
                      container__bst_cmp_type,
                      void*
                     );

/*
    Remove a node from the specified bst

    Syntax:
        Container_RemoveBSTNode(existing_node_ptr, &my_bst);
 */
inline void
Container_RemoveBSTNode (
                         struct container__bst_node* restrict,
                         struct container__bst* restrict
                        );


/*
    Return the state of a bst

    Syntax:
        state = Container_BSTState(&my_bst);
 */
inline enum container__bst_state
Container_BSTState (struct container__bst* restrict);


/*
    Start a scan starting with the specified node in the bst

    Syntax:
        Container_StartBSTScanNode(&my_element.node, &my_bst, &bst_scan);
 */
inline void
Container_StartBSTScanNode (
                            struct container__bst_node* restrict,
                            struct container__bst* restrict,
                            struct container__bst_scan* restrict
                           );

/*
    Start a scan starting with the right most node in the bst

    Syntax:
        Container_StartBSTScanLeft(&my_bst, &bst_scan);
 */
inline void
Container_StartBSTScanLeft (
                            struct container__bst* restrict,
                            struct container__bst_scan* restrict
                           );

/*
    Start a scan starting with the left most node in the bst

    Syntax:
        Container_StartBSTScanRight(&my_bst, &bst_scan);
 */
inline void
Container_StartBSTScanRight (
                             struct container__bst* restrict,
                             struct container__bst_scan* restrict
                            );

/*
    Resume a scan, traversing left

    Syntax:
        Container_ResumeBSTScanLeft(&my_bst, &bst_scan);
 */
inline void
Container_ResumeBSTScanLeft (
                             struct container__bst* restrict,
                             struct container__bst_scan* restrict
                            );

/*
    Resume a scan, traversing right

    Syntax:
        Container_ResumeBSTScanRight(&my_bst, &bst_scan);
 */
inline void
Container_ResumeBSTScanRight (
                              struct container__bst* restrict,
                              struct container__bst_scan* restrict
                             );

/*
    Return the state of a bst scan

    Syntax:
        scan_state = Container_BSTScanState(&bst_scan);
 */
inline enum container__bst_scan_state
Container_BSTScanState (struct container__bst_scan* restrict);


#include <container/utils.h>


inline void
Container_UpdateBSTScan (
                         struct container__bst* restrict,
                         struct container__bst_scan* restrict
                        );


inline void
Container_UpdateBSTScan (
                         struct container__bst* restrict      bst,
                         struct container__bst_scan* restrict scan
                        )
{
    enum container__clist_scan_state state;

    state = Container_CListScanState(&bst->ordering, &scan->ordering_scan);
    if(state == container__clist_scan_incomplete)
    {
        scan->current_node = CONTAINER__CONTAINER_OF(
                                                     scan->ordering_scan.current_node,
                                                     struct container__bst_node,
                                                     ordering_node
                                                    );
    }
    else
        scan->current_node = NULL;
}


inline void
Container_InitBST (struct container__bst* restrict bst)
{
    bst->root = NULL;

    Container_InitCList(&bst->ordering);
}

inline void
Container_ResetBST (struct container__bst* restrict bst)
{
    Container_InitBST(bst);
}

inline enum container__error_code
Container_LookupBSTNode (
                         void*                                 value,
                         struct container__bst* restrict       bst,
                         container__bst_lookup_type            lookup,
                         void*                                 user_data,
                         struct container__bst_node** restrict closest_node
                        )
{
    struct container__bst_node* restrict scan;

    scan = bst->root;

    if(scan == NULL)
        *closest_node = NULL;
    else
    {
        struct container__bst_node* prev;

        do
        {
            enum container__bst_cmp_result result;

            result = (*lookup)(value, scan, user_data);
            if(result == container__bst_node_equal)
            {
                *closest_node = scan;

                return container__error_none;
            }

            prev = scan;

            if(result == container__bst_node_left)
                scan = scan->left;
            else
                scan = scan->right;
        }while(scan != NULL);

        *closest_node = prev;
    }

    return container__error_value_not_found;
}

inline void
Container_AddBSTNode (
                      struct container__bst_node* restrict node,
                      struct container__bst* restrict      bst,
                      container__bst_cmp_type              cmp,
                      void*                                user_data
                     )
{
    struct container__bst_node* root;

    root = bst->root;
    if(root == NULL)
    {
        node->parent = NULL;
        node->left   = NULL;
        node->right  = NULL;

        bst->root = node;

        Container_AddCListHead(&node->ordering_node, &bst->ordering);
    }
    else
        Container_InsBSTNode(node, root, cmp, user_data);
}

inline void
Container_InsBSTNode (
                      struct container__bst_node* restrict new_node,
                      struct container__bst_node* restrict existing_node,
                      container__bst_cmp_type              cmp,
                      void*                                user_data
                     )
{
    struct container__bst_node* scan;

    new_node->left  = NULL;
    new_node->right = NULL;

    scan = existing_node;

    while(1)
    {
        enum container__bst_cmp_result result;

        result = (*cmp)(new_node, scan, user_data);
        if(result == container__bst_node_left)
        {
            struct container__bst_node* restrict next;

            next = scan->left;
            if(next == NULL)
            {
                new_node->parent = scan;
                scan->left       = new_node;

                Container_PrependCListNode(&new_node->ordering_node, &scan->ordering_node);

                break;
            }

            scan = next;
        }
        else
        {
            struct container__bst_node* restrict next;

            next = scan->right;
            if(next == NULL)
            {
                new_node->parent = scan;
                scan->right      = new_node;

                Container_AppendCListNode(&new_node->ordering_node, &scan->ordering_node);

                break;
            }

            scan = next;
        }
    }
}

inline void
Container_RemoveBSTNode (
                         struct container__bst_node* restrict node,
                         struct container__bst* restrict      bst
                        )
{
    struct container__bst_node* restrict parent;
    struct container__bst_node*          move_node;

    Container_RemoveCListNode(&node->ordering_node);

    if(node->left == NULL && node->right == NULL)
        move_node = NULL;
    else if(node->left == NULL)
        move_node = node->right;
    else if(node->right == NULL)
        move_node = node->left;
    else
    {
        struct container__bst_node* node_left;
        struct container__bst_node* node_right;

        node_left  = node->left;
        node_right = node->right;

        move_node = node_right;
        while(move_node->left != NULL)
            move_node = move_node->left;

        move_node->left   = node_left;
        node_left->parent = move_node;

        if(move_node->parent != node)
        {
            struct container__bst_node* restrict move_node_right;
            struct container__bst_node* restrict move_node_parent;

            move_node_parent = move_node->parent;
            move_node_right  = move_node->right;

            move_node_parent->left = move_node_right;
            if(move_node_right != NULL)
                move_node_right->parent = move_node_parent;

            move_node->right   = node_right;
            node_right->parent = move_node;
        }
    }

    parent = node->parent;

    if(parent == NULL)
        bst->root = move_node;
    else
    {
        if(parent->left == node)
            parent->left = move_node;
        else
            parent->right = move_node;
    }

    if(move_node != NULL)
        move_node->parent = parent;
}

inline enum container__bst_state
Container_BSTState (struct container__bst* restrict bst)
{
    if(bst->root == NULL)
        return container__bst_empty;

    return container__bst_populated;
}

inline void
Container_StartBSTScanNode (
                            struct container__bst_node* restrict node,
                            struct container__bst* restrict      bst,
                            struct container__bst_scan* restrict scan
                           )
{
    Container_StartCListScanNode(&node->ordering_node, &scan->ordering_scan);
    Container_UpdateBSTScan(bst, scan);
}

inline void
Container_StartBSTScanLeft (
                            struct container__bst* restrict      bst,
                            struct container__bst_scan* restrict scan
                           )
{

    Container_StartCListScanTail(&bst->ordering, &scan->ordering_scan);
    Container_UpdateBSTScan(bst, scan);
}

inline void
Container_StartBSTScanRight (
                             struct container__bst* restrict      bst,
                             struct container__bst_scan* restrict scan
                            )
{
    Container_StartCListScanHead(&bst->ordering, &scan->ordering_scan);
    Container_UpdateBSTScan(bst, scan);
}

inline void
Container_ResumeBSTScanLeft (
                             struct container__bst* restrict      bst,
                             struct container__bst_scan* restrict scan
                            )
{
    Container_ResumeCListScanPrev(&scan->ordering_scan);
    Container_UpdateBSTScan(bst, scan);
}

inline void
Container_ResumeBSTScanRight (
                              struct container__bst* restrict      bst,
                              struct container__bst_scan* restrict scan
                             )
{
    Container_ResumeCListScanNext(&scan->ordering_scan);
    Container_UpdateBSTScan(bst, scan);
}

inline enum container__bst_scan_state
Container_BSTScanState (struct container__bst_scan* restrict scan)
{
    if(scan->current_node == NULL)
        return container__bst_scan_finished;

    return container__bst_scan_incomplete;
}


#endif
