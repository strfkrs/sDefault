#include "creep.h"
#include "types.h"
#include "room.h"
#include "tools.h"

bool_t cleanupCreeps()
{
   return cleanupPtList( (void **) creeps );
}

bool_t initCreep( Creep * creep, Room * room, ROLE role, JOB job )
{
   if ( !addPtToList( creep, (void *)room->creeps ) )
   {
      return false;
   }
   creep->role = role;
   creep->job = job;
   creep->room = room;

   return true;
}
bool_t initCreepAction( Creep * creep, ACTION action )
{
   creep->actions[ creep->numActions ] = action;
   creep->numActions++;
   return true;
}
index_t amountOfCreepsWithRole( ROLE role )
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