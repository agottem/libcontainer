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
    The clist container stores a circular doubly linked list
 */


#ifndef _CONTAINER__CLIST_H_
#define _CONTAINER__CLIST_H_


/*
    Valid states for this container
 */
enum container__clist_state
{
    container__clist_populated,
    container__clist_empty
};

/*
    Valid states for a scan of this container.  The scan is finished once each node in
    the clist has been visited
 */
enum container__clist_scan_state
{
    container__clist_scan_incomplete,
    container__clist_scan_finished
};


/*
    The node data to be placed in each clist element

    Accessible members:
        next -- the next node
        prev -- the previous node
 */
struct container__clist_node
{
    struct container__clist_node* next;
    struct container__clist_node* prev;
};

/*
    The container itself

    Accessible members:
        sentinel -- access sentinel.next or sentinel.prev for the head or tail of the clist
 */
struct container__clist
{
    struct container__clist_node sentinel;
};

/*
    The scan structure is used to track the current position of a container scan

    Accessible members:
        current_node -- the current element node being visited
 */
struct container__clist_scan
{
    struct container__clist_node* current_node;
};


/*
    Initialize a clist container.  The container will be empty upon initialization

    Syntax:
        Container_InitCList(&my_clist);
 */
inline void
Container_InitCList (struct container__clist* restrict);

/*
    Reset a clist container to the initialized state

    Syntax:
        Container_ResetCList(&my_clist);
 */
inline void
Container_ResetCList (struct container__clist* restrict);


/*
    Place the contents of one clist at the head of another.  The clist being placed at the
    head becomes invalid after this operation

    Syntax:
        Container_MergeCListHead(&from_clist, &into_clist);
 */
inline void
Container_MergeCListHead (
                          struct container__clist* restrict,
                          struct container__clist* restrict
                         );

/*
    Place the contents of one clist at the tail of another.  The clist being placed at the
    tail becomes invalid after this operation

    Syntax:
        Container_MergeCListTail(&from_clist, &into_clist);
 */
inline void
Container_MergeCListTail (
                          struct container__clist* restrict,
                          struct container__clist* restrict
                         );

/*
    Place an existing clist before the specified node, invalidating the specified clist upon
    completion

    Syntax:
        Container_PrependCList(&my_element.node, &my_clist);
 */
inline void
Container_PrependCList (
                        struct container__clist_node* restrict,
                        struct container__clist* restrict
                       );

/*
    Place an existing clist after the specified node, invalidating the specified clist upon
    completion

    Syntax:
        Container_AppendCList(&my_element.node, &my_clist);
 */
inline void
Container_AppendCList (
                       struct container__clist_node* restrict,
                       struct container__clist* restrict
                      );

/*
     Split a clist, with the new clist containing all nodes from the specified node to the tail

     Syntax:
         Container_SplitCListBefore(&my_element.node, &my_clist, &new_clist);
 */
inline void
Container_SplitCListBefore (
                            struct container__clist_node* restrict,
                            struct container__clist* restrict,
                            struct container__clist* restrict
                           );

/*
    Split a clist, with the new clist containing all nodes after the specified node

    Syntax:
        Container_SplitCListAfter(&my_element.node, &my_clist, &new_clist);
 */
inline void
Container_SplitCListAfter (
                           struct container__clist_node* restrict,
                           struct container__clist* restrict,
                           struct container__clist* restrict
                          );


/*
    Add a node to the head of the specified clist

    Syntax:
        Container_AddCListHead(&my_element.node, &my_clist);
 */
inline void
Container_AddCListHead (
                        struct container__clist_node* restrict,
                        struct container__clist* restrict
                       );

/*
    Remove the head node from a clist

    Syntax:
        Container_RemoveCListHead(&my_clist);
 */
inline void
Container_RemoveCListHead (struct container__clist* restrict);

/*
    Add a node to the tail of the specified clist

    Syntax:
        Container_AddCListTail(&my_element.node, &my_clist);
 */
inline void
Container_AddCListTail (
                        struct container__clist_node* restrict,
                        struct container__clist* restrict
                       );

/*
    Remove the tail node from a clist

    Syntax:
        Container_RemoveCListTail(&my_clist);
 */
inline void
Container_RemoveCListTail (struct container__clist* restrict);

/*
    Add a node before the specified node in the clist

    Syntax:
        Container_PrependCListNode(&new_element.node, &existing_element.node);
 */
inline void
Container_PrependCListNode (
                            struct container__clist_node* restrict,
                            struct container__clist_node* restrict
                           );

/*
    Add a node after the specified node in the clist

    Syntax:
        Container_AppendCListNode(&new_element.node, &existing_element.node);
 */
inline void
Container_AppendCListNode (
                           struct container__clist_node* restrict,
                           struct container__clist_node* restrict
                          );

/*
    Remove the specified node from its clist

    Syntax:
        Container_RemoveCListNode(&my_element.node);
 */
inline void
Container_RemoveCListNode (struct container__clist_node* restrict);


/*
    Return the state of the clist

    Syntax:
        state = Container_CListState(&my_clist);
 */
inline enum container__clist_state
Container_CListState (struct container__clist* restrict);


/*
    Start a clist scan from the specified node

    Syntax:
        Container_StartCListScanNode(&my_element.node, &clist_scan);
 */
inline void
Container_StartCListScanNode (
                              struct container__clist_node* restrict,
                              struct container__clist_scan* restrict
                             );

/*
    Start a clist scan from the head node

    Syntax:
        Container_StartCListScanHead(&my_clist, &clist_scan);
 */
inline void
Container_StartCListScanHead (
                              struct container__clist* restrict,
                              struct container__clist_scan* restrict
                             );

/*
    Start a clist scan from the tail node

    Syntax:
        Container_StartCListScanTail(&my_clist, &clist_scan);
 */
inline void
Container_StartCListScanTail (
                              struct container__clist* restrict,
                              struct container__clist_scan* restrict
                             );

/*
    Resume a clist scan traversing towards the tail

    Syntax:
        Container_ResumeCListScanNext(&clist_scan);
 */
inline void
Container_ResumeCListScanNext (struct container__clist_scan* restrict);

/*
    Resume a clist scan traversing towards the head

    Syntax:
        Container_ResumeCListScanPrev(&clist_scan);
 */
inline void
Container_ResumeCListScanPrev (struct container__clist_scan* restrict);

/*
    Return the state of a clist scan

    Syntax:
        scan_state = Container_CListScanState(&my_clist, &clist_scan);
 */
inline enum container__clist_scan_state
Container_CListScanState (
                          struct container__clist* restrict,
                          struct container__clist_scan* restrict
                         );


inline void
Container_InitCList (struct container__clist* restrict clist)
{
    clist->sentinel.next = &clist->sentinel;
    clist->sentinel.prev = &clist->sentinel;
}

inline void
Container_ResetCList (struct container__clist* restrict clist)
{
    Container_InitCList(clist);
}

inline void
Container_MergeCListHead (
                          struct container__clist* restrict source,
                          struct container__clist* restrict dest
                         )
{
    Container_AppendCList(&dest->sentinel, source);
}

inline void
Container_MergeCListTail (
                          struct container__clist* restrict source,
                          struct container__clist* restrict dest
                         )
{
    Container_PrependCList(&dest->sentinel, source);
}

inline void
Container_PrependCList (
                        struct container__clist_node* restrict node,
                        struct container__clist* restrict      clist
                       )
{
    struct container__clist_node* node_prev;
    struct container__clist_node* clist_next;
    struct container__clist_node* clist_prev;
    enum container__clist_state   state;

    state = Container_CListState(clist);
    if(state == container__clist_empty)
        return;

    clist_prev = clist->sentinel.prev;
    clist_next = clist->sentinel.next;
    node_prev  = node->prev;

    node_prev->next  = clist_next;
    clist_next->prev = node_prev;

    node->prev       = clist_prev;
    clist_prev->next = node;
}

inline void
Container_AppendCList (
                       struct container__clist_node* restrict node,
                       struct container__clist* restrict      clist
                      )
{
    struct container__clist_node* node_next;
    struct container__clist_node* clist_prev;
    struct container__clist_node* clist_next;
    enum container__clist_state   state;

    state = Container_CListState(clist);
    if(state == container__clist_empty)
        return;

    clist_next = clist->sentinel.next;
    clist_prev = clist->sentinel.prev;
    node_next  = node->next;

    node_next->prev  = clist_prev;
    clist_prev->next = node_next;

    node->next       = clist_next;
    clist_next->prev = node;
}

inline void
Container_SplitCListBefore (
                            struct container__clist_node* restrict node,
                            struct container__clist* restrict      source_clist,
                            struct container__clist* restrict      new_clist
                           )
{
    struct container__clist_node* restrict node_prev;
    struct container__clist_node*          source_prev;

    source_prev = source_clist->sentinel.prev;
    node_prev   = node->prev;

    new_clist->sentinel.next = node;
    new_clist->sentinel.prev = source_prev;

    source_prev->next           = &new_clist->sentinel;
    source_clist->sentinel.prev = node_prev;

    node_prev->next = &source_clist->sentinel;
    node->prev      = &new_clist->sentinel;
}

inline void
Container_SplitCListAfter (
                           struct container__clist_node* restrict node,
                           struct container__clist* restrict      source_clist,
                           struct container__clist* restrict      new_clist
                          )
{
    struct container__clist_node* restrict node_next;
    struct container__clist_node*          source_prev;

    node_next = node->next;
    if(node_next == &source_clist->sentinel)
    {
        new_clist->sentinel.next = &new_clist->sentinel;
        new_clist->sentinel.prev = &new_clist->sentinel;

        return;
    }

    source_prev = source_clist->sentinel.prev;

    new_clist->sentinel.next = node_next;
    new_clist->sentinel.prev = source_prev;

    source_prev->next           = &new_clist->sentinel;
    source_clist->sentinel.prev = node;

    node->next      = &source_clist->sentinel;
    node_next->prev = &new_clist->sentinel;
}

inline void
Container_AddCListHead (
                        struct container__clist_node* restrict node,
                        struct container__clist* restrict      clist
                       )
{
    struct container__clist_node* sentinel;
    struct container__clist_node* next;

    sentinel = &clist->sentinel;
    next     = sentinel->next;

    node->prev = sentinel;
    node->next = next;
    next->prev = node;

    sentinel->next = node;
}

inline void
Container_RemoveCListHead (struct container__clist* restrict clist)
{
    clist->sentinel.next       = clist->sentinel.next->next;
    clist->sentinel.next->prev = &clist->sentinel;
}

inline void
Container_AddCListTail (
                        struct container__clist_node* restrict node,
                        struct container__clist* restrict      clist
                       )
{
    struct container__clist_node* sentinel;
    struct container__clist_node* prev;

    sentinel = &clist->sentinel;
    prev     = sentinel->prev;

    node->next = sentinel;
    node->prev = prev;
    prev->next = node;

    sentinel->prev = node;
}

inline void
Container_RemoveCListTail (struct container__clist* restrict clist)
{
    clist->sentinel.prev       = clist->sentinel.prev->prev;
    clist->sentinel.prev->next = &clist->sentinel;
}

inline void
Container_PrependCListNode (
                            struct container__clist_node* restrict new_node,
                            struct container__clist_node* restrict existing_node
                           )
{
    struct container__clist_node* prev;

    prev = existing_node->prev;

    prev->next     = new_node;
    new_node->prev = prev;
    new_node->next = existing_node;

    existing_node->prev = new_node;
}

inline void
Container_AppendCListNode (
                           struct container__clist_node* restrict new_node,
                           struct container__clist_node* restrict existing_node
                          )
{
    struct container__clist_node* next;

    next = existing_node->next;

    next->prev     = new_node;
    new_node->next = next;
    new_node->prev = existing_node;

    existing_node->next = new_node;
}

inline void
Container_RemoveCListNode (struct container__clist_node* restrict node)
{
    struct container__clist_node* next;
    struct container__clist_node* prev;

    next = node->next;
    prev = node->prev;

    prev->next = next;
    next->prev = prev;
}

inline enum container__clist_state
Container_CListState (struct container__clist* restrict clist)
{
    if(clist->sentinel.next == &clist->sentinel)
        return container__clist_empty;

    return container__clist_populated;
}

inline void
Container_StartCListScanNode (
                              struct container__clist_node* restrict node,
                              struct container__clist_scan* restrict scan
                             )
{
    scan->current_node = node;
}

inline void
Container_StartCListScanHead (
                              struct container__clist* restrict      clist,
                              struct container__clist_scan* restrict scan
                             )
{
    Container_StartCListScanNode(clist->sentinel.next, scan);
}

inline void
Container_StartCListScanTail (
                              struct container__clist* restrict      clist,
                              struct container__clist_scan* restrict scan
                             )
{
    Container_StartCListScanNode(clist->sentinel.prev, scan);
}

inline void
Container_ResumeCListScanNext (struct container__clist_scan* restrict scan)
{
    scan->current_node = scan->current_node->next;
}

inline void
Container_ResumeCListScanPrev (struct container__clist_scan* restrict scan)
{
    scan->current_node = scan->current_node->prev;
}

inline enum container__clist_scan_state
Container_CListScanState (
                          struct container__clist* restrict      clist,
                          struct container__clist_scan* restrict scan
                         )
{
    if(scan->current_node == &clist->sentinel)
        return container__clist_scan_finished;

    return container__clist_scan_incomplete;
}


#endif
