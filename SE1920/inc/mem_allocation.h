#ifndef MEM_ALLOCATION_H_
#define MEM_ALLOCATION_H_

#include "FreeRTOS.h"

static inline void* my_malloc(int size){ return (pvPortMalloc(size));}

static inline void my_free(void * ptr) {vPortFree(ptr);}

#endif
