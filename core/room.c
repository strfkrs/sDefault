#include "room.h"
#include "creep.h"
#include "spawn.h"
#include "types.h"
#include "tools.h"

bool_t cleanupRooms()
{
   return cleanupPtList( (void **) rooms );
}

Room * getRoomByIndex( index_t idx )
{
   return ( idx < MAX_ROOMS ) ? &core_rooms[idx] : NULL;
}

bool_t initRoom( index_t idx )
{
   rooms[idx] = &core_rooms[idx];
   Room * room = rooms[idx];

   if ( ! cleanupPtList( (void **) room->spawns ) )
   {
      return false;
   }
   if ( ! cleanupPtList( (void **) room->creeps ) )
   {
      return false;
   }

   return true;
}