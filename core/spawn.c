#include "spawn.h"
#include "room.h"
#include "tools.h"

bool_t cleanupSpawns()
{
   return cleanupPtList( (void **)  spawns );
}

bool_t initSpawn( Spawn * spawn, Room * room, bool_t working )
{
   if ( !addPtToList( spawn, (void *)room->spawns ) )
   {
      return false;
   }
   spawn->working = working;
   return true;
}