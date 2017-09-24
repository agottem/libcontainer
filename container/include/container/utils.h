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
    Defines utility functions for use with the container library
 */


#ifndef _CONTAINER__UTILS_H_
#define _CONTAINER__UTILS_H_


#include <stddef.h>


/*
    Returns a pointer to the container of the specified type

    For example:
        struct my_element
        {
            int my_int;

            struct container_node my_node;
        };

        struct container_node* node_ptr = ContainerHead();

        struct my_element* my_el = CONTAINER__CONTAINER_OF(node_ptr, struct my_element, my_node);
 */
#define CONTAINER__CONTAINER_OF(address, type, member) ((void*)((char*)address-offsetof(type, member)))

/*
    Returns a pointer to the container of the specified type using std container types

    For example:
        struct my_element
        {
            int my_int;

            struct std_container_node my_node;
        };

        struct std_container_node* node_ptr = StdContainerHead();

        struct my_element* my_el = CONTAINER__STD_CONTAINER_OF(node_ptr, struct my_element, my_node);
 */
#define CONTAINER__STD_CONTAINER_OF(address, type, member) CONTAINER__CONTAINER_OF(address, type, member.node)


#endif
