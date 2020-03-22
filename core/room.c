#include "room.h"
#include "creep.h"
#include "spawn.h"
#include "types.h"
#include "tools.h"

bool_t cleanupRooms()
{
   return cleanupPtList( (void **) rooms );
}

bool_t initRoom( Room * room  )
{
   if ( ! addPtToList( room, (void *)rooms ) )
   {
      return false;
   }

   for( index_t s = 0; s < LENGTHOF_SPAWNS( room->spawns ); s++ )
   {
      room->spawns[s] = NULL;
   }

   for( index_t c = 0; c < LENGTHOF_CREEPS( room->creeps ); c++ )
   {
      room->creeps[c] = NULL;
   }

   return true;
}

bool_t addSpawnToRoom( Room * room, Spawn * spawn )
{
   if ( addPtToList( spawn, (void *)rooms ) )
   {
      spawn->room = room;
      return true;
   }
   return false;
}