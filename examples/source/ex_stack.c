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


#include <stdlib.h>
#include <stdio.h>
#include <container/error.h>
#include <container/stack.h>


#define STACK_SIZE 64


/* The type we'll be making a stack of */
struct my_data_entry
{
    int my_data;
};


int main (int argument_count, char** arguments)
{
    struct my_data_entry    stack_data[STACK_SIZE];
    struct container__stack my_stack;
    int                     count;

    count = 0;

    Container_InitStack(STACK_SIZE, &my_stack);

    while(Container_PushStack(1, &my_stack) == container__error_none)
    {
        stack_data[my_stack.top].my_data = count;
        count++;
    }

    while(Container_StackState(&my_stack) != container__stack_empty)
    {
        printf("Stack value: %d\n", stack_data[my_stack.top].my_data);

        Container_PopStack(1, &my_stack);
    }

    return EXIT_SUCCESS;
}
