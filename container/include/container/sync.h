#ifndef _CONTAINER__SYNC_H_
#define _CONTAINER__SYNC_H_


typedef void
(*container__lock_sync_type)   (void*);

typedef void
(*container__unlock_sync_type) (void*);


inline void
Container_LockSync (void*, container__lock_sync_type);

inline void
Container_UnlockSync (void*, container__unlock_sync_type);


#include <stddef.h>


inline void
Container_LockSync (void* user_data, container__lock_sync_type lock_sync)
{
    if(lock_sync != NULL)
        lock_sync(user_data);
}

inline void
Container_UnlockSync (void* user_data, container__unlock_sync_type unlock_sync)
{
    if(unlock_sync != NULL)
        unlock_sync(user_data);
}


#endif
