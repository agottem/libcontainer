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
    The queue container stores a singly linked list with efficient insertion at the tail or head
 */


#ifndef _CONTAINER__QUEUE_H_
#define _CONTAINER__QUEUE_H_


/*
    Valid states for this container
 */
enum container__queue_state
{
    container__queue_populated,
    container__queue_empty
};

/*
    Valid states for a scan of this container
 */
enum container__queue_scan_state
{
    container__queue_scan_incomplete,
    container__queue_scan_finished
};


/*
    The node data to be placed in each queue element

    Accessible members:
        next -- the next node
 */
struct container__queue_node
{
    struct container__queue_node* next;
};

/*
    The container itself

    Accessible members:
        head -- the head node of the queue
        tail -- the tail node of the queue
 */
struct container__queue
{
    struct container__queue_node* head;
    struct container__queue_node* tail;
};

/*
    The scan structure used to track the current position of a container scan

    Accessible members:
        current_node -- the current element node being visited
 */
struct container__queue_scan
{
    struct container__queue_node* current_node;
};


/*
    Initialize a queue container.  The container will be empty upon initialization

    Syntax:
        Container_InitQueue(&my_queue);
 */
inline void
Container_InitQueue (struct container__queue* restrict);

/*
    Reset a queue container to the initialized state

    Syntax:
        Container_ResetQueue(&my_queue);
 */
inline void
Container_ResetQueue (struct container__queue* restrict);


/*
    Place the contents of one queue at the head of another.  The queue being placed at the
    head becomes invalid after this operation

    Syntax:
        Container_MergeQueueHead(&from_queue, &into_queue);
 */
inline void
Container_MergeQueueHead (
                          struct container__queue* restrict,
                          struct container__queue* restrict
                         );

/*
    Place the contents of one queue at the tail of another.  The queue being placed at the
    tail becomes invalid after this operation

    Syntax:
        Container_MergeQueueTail(&from_queue, &into_queue);
 */
inline void
Container_MergeQueueTail (
                          struct container__queue* restrict,
                          struct container__queue* restrict
                         );


/*
    Add a node to the head of a queue

    Syntax:
        Container_AddQueueHead(&my_element.node, &my_queue);
 */
inline void
Container_AddQueueHead (
                        struct container__queue_node* restrict,
                        struct container__queue* restrict
                       );

/*
    Remove the node at the head of a queue

    Syntax:
        Container_RemoveQueueHead(&my_queue);
 */
inline void
Container_RemoveQueueHead (struct container__queue* restrict);

/*
    Add a node to the tail of a queue

    Syntax:
        Container_AddQueueTail(&my_element.node, &my_queue);
 */
inline void
Container_AddQueueTail (
                        struct container__queue_node* restrict,
                        struct container__queue* restrict
                       );


/*
    Return the state of the queue

    Syntax:
        state = Container_QueueState(&my_queue);
 */
inline enum container__queue_state
Container_QueueState (struct container__queue* restrict);


/*
    Start a queue scan from a specific node

    Syntax:
        Container_StartQueueScanNode(&my_element.node, &queue_scan);
 */
inline void
Container_StartQueueScanNode (
                              struct container__queue_node* restrict,
                              struct container__queue_scan* restrict
                             );

/*
    Start a queue scan

    Syntax:
        Container_StartQueueScan(&my_queue, &queue_scan);
 */
inline void
Container_StartQueueScan (
                          struct container__queue* restrict,
                          struct container__queue_scan* restrict
                         );

/*
    Resume a queue scan traversing towards the tail

    Syntax:
        Container_ResumeQueueScan(&queue_scan);
 */

inline void
Container_ResumeQueueScan (struct container__queue_scan* restrict);

/*
    Return the state of a queue scan

    Syntax:
        scan_state = Container_QueueScanState(&queue_scan);
 */
inline enum container__queue_scan_state
Container_QueueScanState (struct container__queue_scan* restrict);


#include <stddef.h>


inline void
Container_InitQueue (struct container__queue* restrict queue)
{
    queue->head = NULL;
}

inline void
Container_ResetQueue (struct container__queue* restrict queue)
{
    Container_InitQueue(queue);
}

inline void
Container_MergeQueueHead (
                          struct container__queue* restrict source,
                          struct container__queue* restrict dest
                         )
{
    struct container__queue_node* restrict source_head;
    struct container__queue_node* restrict dest_head;

    source_head = source->head;
    if(source_head == NULL)
        return;

    dest_head = dest->head;

    source->tail->next = dest_head;
    if(dest_head == NULL)
        dest->tail = source->tail;

    dest->head = source_head;
}

inline void
Container_MergeQueueTail (
                          struct container__queue* restrict source,
                          struct container__queue* restrict dest
                         )
{
    struct container__queue_node* restrict source_head;

    source_head = source->head;
    if(source_head == NULL)
        return;

    if(dest->head != NULL)
        dest->tail->next = source->head;
    else
        dest->head = source_head;

    dest->tail = source->tail;
}

inline void
Container_AddQueueHead (
                        struct container__queue_node* restrict node,
                        struct container__queue* restrict      queue
                       )
{
    node->next = queue->head;

    if(queue->head == NULL)
        queue->tail = node;

    queue->head = node;
}

inline void
Container_RemoveQueueHead (struct container__queue* restrict queue)
{
    queue->head = queue->head->next;
}

inline void
Container_AddQueueTail (
                        struct container__queue_node* restrict node,
                        struct container__queue* restrict      queue
                       )
{
    node->next = NULL;

    if(queue->head != NULL)
        queue->tail->next = node;
    else
        queue->head = node;

    queue->tail = node;
}

inline enum container__queue_state
Container_QueueState (struct container__queue* restrict queue)
{
    if(queue->head == NULL)
        return container__queue_empty;

    return container__queue_populated;
}

inline void
Container_StartQueueScanNode (
                              struct container__queue_node* restrict node,
                              struct container__queue_scan* restrict scan
                             )
{
    scan->current_node = node;
}

inline void
Container_StartQueueScan (
                          struct container__queue* restrict      queue,
                          struct container__queue_scan* restrict scan
                         )
{
    Container_StartQueueScanNode(queue->head, scan);
}

inline void
Container_ResumeQueueScan (struct container__queue_scan* restrict scan)
{
    scan->current_node = scan->current_node->next;
}

inline enum container__queue_scan_state
Container_QueueScanState (struct container__queue_scan* restrict scan)
{
    if(scan->current_node == NULL)
        return container__queue_scan_finished;

    return container__queue_scan_incomplete;
}


#endif
