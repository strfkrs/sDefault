#include "creep.h"
#include "types.h"
#include "room.h"
#include "tools.h"

bool_t cleanupCreeps()
{
   return cleanupPtList( (void **) creeps );
}

Creep * getCreepByIndex( index_t idx )
{
   return &core_creeps[idx];
}

bool_t initCreep( index_t idx, index_t roomIdx, ROLE role, JOB job )
{
   Creep * creep = getCreepByIndex( idx );
   Room * room = getRoomByIndex( roomIdx );

   if ( !addPtToList( creep, (void *)room->creeps ) )
   {
      return false;
   }
   creep->role = role;
   creep->job = job;
   creep->room = room;

   return true;
}
bool_t initCreepAction( index_t creepIdx, ACTION action )
{
   Creep * creep = getCreepByIndex( creepIdx );
   creep->actions[ creep->numActions ] = action;
   creep->numActions++;
   return true;
}
index_t getAmountOfCreepsWithRole( ROLE role )
{
   index_t amount = 0;
   for ( index_t c = 0; c < MAX_CREEPS; c++ )
   {
      if ( creeps[c] != NULL && creeps[c]->role == role )
      {
         amount++;
      }
   }
   return amount;
}