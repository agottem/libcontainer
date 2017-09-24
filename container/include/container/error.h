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


#ifndef _CONTAINER__ERROR_H_
#define _CONTAINER__ERROR_H_


/*
   Error codes that may be returned by various container functions
 */
enum container__error_code
{
    container__error_none,
    container__error_value_not_found,
    container__error_resource_unavailable,
    container__error_memory_alloc
};


#endif
