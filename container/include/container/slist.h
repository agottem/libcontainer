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
    The slist container stores a singly linked list
 */


#ifndef _CONTAINER__SLIST_H_
#define _CONTAINER__SLIST_H_


/*
    Valid states for this container
 */
enum container__slist_state
{
    container__slist_populated,
    container__slist_empty
};

/*
    Valid states for a scan of this container
 */
enum container__slist_scan_state
{
    container__slist_scan_incomplete,
    container__slist_scan_finished
};


/*
    The node data to be placed in each slist element

    Accessible members:
        next -- the next node in the list
 */
struct container__slist_node
{
    struct container__slist_node* next;
};

/*
    The container itself

    Accessible members:
        head -- the first element node in the list
 */
struct container__slist
{
    struct container__slist_node* head;
};

/*
    The scan structure is used to track the current position of a container scan

    Accessible members:
        current_node -- the current element node being visited
 */
struct container__slist_scan
{
    struct container__slist_node* current_node;
};


/*
    Initialize an slist container.  The container will be empty upon initialization

    Syntax:
        Container_InitSList(&my_slist);
 */
inline void
Container_InitSList (struct container__slist* restrict);

/*
    Reset an slist container to the initialized state

    Syntax:
        Container_ResetSList(&my_slist);
 */
inline void
Container_ResetSList (struct container__slist* restrict);


/*
    Add a node to the front of the slist

    Syntax:
        Container_AddSListHead(&my_element.node, &my_slist);
 */
inline void
Container_AddSListHead (
                        struct container__slist_node* restrict,
                        struct container__slist* restrict
                       );

/*
    Remove the node at the front of the slist

    Syntax:
        Container_RemoveSListHead(&my_slist);
 */
inline void
Container_RemoveSListHead (struct container__slist* restrict);


/*
    Return the state of the slist container

    Syntax:
        state = Container_SListState(&my_slist);
 */
inline enum container__slist_state
Container_SListState (struct container__slist* restrict);


/*
    Start a scan of of the slist from the specified node

    Syntax:
        Container_StartSListScanNode(&my_element.node, &scan_slist);
 */
inline void
Container_StartSListScanNode (
                              struct container__slist_node* restrict,
                              struct container__slist_scan* restrict
                             );

/*
    Start a scan of all slist nodes, beginning at the head

    Syntax:
        Container_StartSListScan(&my_slist, &scan_slist);
 */
inline void
Container_StartSListScan (
                          struct container__slist* restrict,
                          struct container__slist_scan* restrict
                         );

/*
    Continue to the next node closest to the tail

    Syntax:
        Container_ResumeSListScan(&scan_slist);
 */
inline void
Container_ResumeSListScan (struct container__slist_scan* restrict);

/*
    Return the state of the scan

    Syntax:
        scan_state = ContainerSListScanState(&scan_slist);
 */
inline enum container__slist_scan_state
Container_SListScanState (struct container__slist_scan* restrict);


#include <stddef.h>


inline void
Container_InitSList (struct container__slist* restrict slist)
{
    slist->head = NULL;
}

inline void
Container_ResetSList (struct container__slist* restrict slist)
{
    Container_InitSList(slist);
}

inline void
Container_AddSListHead (
                        struct container__slist_node* restrict node,
                        struct container__slist* restrict      slist
                       )
{
    node->next  = slist->head;
    slist->head = node;
}

inline void
Container_RemoveSListHead (struct container__slist* restrict slist)
{
    slist->head = slist->head->next;
}

inline enum container__slist_state
Container_SListState (struct container__slist* restrict slist)
{
    if(slist->head == NULL)
        return container__slist_empty;

    return container__slist_populated;
}

inline void
Container_StartSListScanNode (
                              struct container__slist_node* restrict node,
                              struct container__slist_scan* restrict scan
                             )
{
    scan->current_node = node;
}


inline void
Container_StartSListScan (
                          struct container__slist* restrict      slist,
                          struct container__slist_scan* restrict scan
                         )
{
    Container_StartSListScanNode(slist->head, scan);
}

inline void
Container_ResumeSListScan (struct container__slist_scan* restrict scan)
{
    scan->current_node = scan->current_node->next;
}

inline enum container__slist_scan_state
Container_SListScanState (struct container__slist_scan* restrict scan)
{
    if(scan->current_node == NULL)
        return container__slist_scan_finished;

    return container__slist_scan_incomplete;
}


#endif
