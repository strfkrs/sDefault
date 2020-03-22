#pragma once
#include "types.h"
#include "room.h"
#include "creep.h"
#include "spawn.h"
#include "coreMsg.h"
#include "order.h"

typedef enum CORE_RETURN
{
   CORE_RETURN_OK,
   CORE_RETURN_ERROR
} CORE_RETURN;

typedef enum CORE_RETURN_BOOL
{
   CORE_RETURN_FALSE,
   CORE_RETURN_TRUE
} CORE_RETURN_BOOL;

typedef index_t CORE_RETURN_SHORT;
typedef void * CORE_RETURN_HEAP_IDX;

static CORE_RETURN_BOOL coreIsInitialized;