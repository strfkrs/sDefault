#include "coreApi.h"
#include "types.h"
#include "creep.h"
#include "room.h"
#include "spawn.h"
#include "tools.h"

CORE_RETURN init()
{
   for( index_t r = 0; r < LENGTHOF( initializedRooms ); r++ )
   {
      if ( initializedRooms[r] != NULL )
      {
         initializedRooms[r] = NULL;
      }
   }
   currentInitializedRoom = NULL;
   return CORE_RETURN_OK;
}

CORE_RETURN init_room( index_t idx  )
{
   * currentInitializedRoom = &rooms[idx];

   if ( !initRoom( * ( currentInitializedRoom++ ) ) )
   {
      return CORE_RETURN_ERROR;
   }
   return CORE_RETURN_OK;
}

CORE_RETURN init_creep( index_t idx, index_t roomIdx, ROLE role, JOB job )
{
   return ( initCreep( &creeps[idx], &rooms[roomIdx], role, job ) )
        ? CORE_RETURN_OK
        : CORE_RETURN_ERROR;
}

CORE_RETURN init_creep_action( index_t idx, ACTION action )
{
   return ( initCreepAction( &creeps[idx], action ) )
        ? CORE_RETURN_OK
        : CORE_RETURN_ERROR;
}