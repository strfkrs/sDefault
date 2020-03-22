#include "spawn.h"
#include "room.h"
#include "tools.h"

bool_t cleanupSpawns()
{
   return cleanupPtList( (void **)  spawns );
}
index_t getSpawnIndex( Spawn * spawn )
{
   for ( index_t c = 0; c < MAX_SPAWNS; c++ )
   {
      if ( spawn == spawns[c] )
      {
         return c;
      }
   }
   return MAX_SPAWNS;
}

Spawn * getSpawnByIndex( index_t idx )
{
   return &core_spawns[idx];
}

bool_t initSpawn( index_t idx, index_t roomIdx, bool_t working )
{
   Spawn * spawn = getSpawnByIndex( idx );
   Room * room = getRoomByIndex( roomIdx );

   if ( !addPtToList( spawn, (void *)room->spawns ) )
   {
      return false;
   }
   spawn->working = working;
   return true;
}

index_t getIdleSpawnCountInRoom( Room * room )
{
   index_t count = 0;
   for ( index_t c = 0; c < MAX_SPAWNS_PER_ROOM && room->spawns[c] != NULL; c++ )
   {
      if ( ! room->spawns[c]->working )
      {
         count++;
      }
   }
   return count;
}