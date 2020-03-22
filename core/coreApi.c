#include "coreApi.h"
#include "types.h"
#include "creep.h"
#include "room.h"
#include "spawn.h"
#include "tools.h"

CORE_RETURN_BOOL is_initialized()
{
   return coreIsInitialized;
}

CORE_RETURN_SHORT init()
{
   bool_t ret = cleanupRooms() ? 0 : 1;
   ret = ret > 0 || cleanupCreeps() ? 0 : 2;
   ret = ret > 0 || cleanupSpawns() ? 0 : 3;
   ret = ret > 0 || cleanupRooms() ? 0 : 4;
   coreIsInitialized = CORE_RETURN_TRUE;
   return ret;
}

CORE_RETURN init_room( index_t idx )
{
   return ( initRoom( idx ) )
        ? CORE_RETURN_OK : CORE_RETURN_ERROR;
}

CORE_RETURN init_creep( index_t idx, index_t roomIdx, ROLE role, JOB job )
{
   return ( initCreep( idx, roomIdx, role, job ) ) ? CORE_RETURN_OK : CORE_RETURN_ERROR;
}

CORE_RETURN init_creep_action( index_t idx, ACTION action )
{
   return ( initCreepAction( idx, action ) ) ? CORE_RETURN_OK : CORE_RETURN_ERROR;
}

CORE_RETURN init_spawn( index_t idx, index_t roomIdx, bool_t spawning )
{
   return ( initSpawn( idx, roomIdx, spawning ) ) ? CORE_RETURN_OK : CORE_RETURN_ERROR;
}

CORE_RETURN_SHORT create_orders()
{
   return createOrders();
}

CORE_RETURN_SHORT get_waiting_orders_count()
{
   return getWaitingOrdersCount();
}

CORE_RETURN_HEAP_IDX get_next_order_byte_idx()
{
   return getNextOrderByteIdx();
}
