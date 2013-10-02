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
    The stack container simply tracks the position and state of a stack
 */


#ifndef _CONTAINER__STACK_H_
#define _CONTAINER__STACK_H_


#include <stddef.h>

#include <container/error.h>


/*
    Valid states for this container
 */
enum container__stack_state
{
    container__stack_populated,
    container__stack_full,
    container__stack_empty
};


/*
    The container itself

    Accessible memebers:
        top     -- the current element at the top of the stack
        max_top -- one beyond the last valid element in a stack
 */
struct container__stack
{
    size_t top;
    size_t max_top;
};


/*
    Initialize a stack container.  The container will be empty upon initialization

    Syntax:
        Container_InitStack(max_number_of_elements, &my_stack);
 */
inline void
Container_InitStack (size_t, struct container__stack* restrict);

/*
    Reset a stack container to the initialized state

    Syntax:
        Container_ResetStack(&my_stack);
 */
inline void
Container_ResetStack (struct container__stack* restrict);


/*
    Push the specified number of elements onto the stack, returning an error if the operation could
    not be performed successfully

    Syntax:
        error = Container_PushStack(number_of_elements, &my_stack);
 */
inline enum container__error_code
Container_PushStack (size_t, struct container__stack* restrict);

/*
    Pop the specified number of elements from the stack

    Syntax:
        Container_PopStack(number_of_elements, &my_stack);
 */
inline void
Container_PopStack (size_t, struct container__stack* restrict);


/*
    Return the state of the stack

    Syntax:
        state = Container_StackState(&my_stack);
 */
inline enum container__stack_state
Container_StackState (struct container__stack* restrict);


inline void
Container_InitStack (size_t max_top, struct container__stack* restrict stack)
{
    stack->top     = max_top;
    stack->max_top = max_top;
}

inline void
Container_ResetStack (struct container__stack* restrict stack)
{
    stack->top = stack->max_top;
}

inline enum container__error_code
Container_PushStack (
                     size_t                            count,
                     struct container__stack* restrict stack
                    )
{
    if(count > stack->top)
        return container__error_resource_unavailable;

    stack->top -= count;

    return container__error_none;
}

inline void
Container_PopStack (size_t count, struct container__stack* restrict stack)
{
    stack->top += count;
}

inline enum container__stack_state
Container_StackState (struct container__stack* restrict stack)
{
    size_t top;

    top = stack->top;

    if(top == 0)
        return container__stack_full;
    else if(top == stack->max_top)
        return container__stack_empty;

    return container__stack_populated;
}


#endif
