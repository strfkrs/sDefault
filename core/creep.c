#include "creep.h"
#include "types.h"
#include "room.h"

bool_t initCreep( creep * creep, room * room, ROLE role, JOB job )
{

   creep->role = role;
   creep->job = job;
   creep->room = room;

   return true;
}
bool_t initCreepAction( creep * creep, ACTION action )
{
   creep->actions[ creep->numActions ] = action;
   creep->numActions++;
   return true;
}