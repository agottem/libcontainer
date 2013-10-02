#include <container/stack.h>


extern void
Container_InitStack (size_t, struct container__stack* restrict);

extern void
Container_ResetStack (struct container__stack* restrict);


extern enum container__error_code
Container_PushStack (size_t, struct container__stack* restrict);

extern void
Container_PopStack (size_t, struct container__stack* restrict);


extern enum container__stack_state
Container_StackState (struct container__stack* restrict);
