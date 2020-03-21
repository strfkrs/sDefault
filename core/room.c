#include "room.h"
#include "types.h"
#include "tools.h"

bool_t initRoom( room * room  )
{
   for( index_t s = 0; s < LENGTHOF( initializedRooms[r]->spawns ); s++ )
   {
      initializedRooms[r]->spawns[s] = NULL;
   }
   for( index_t c = 0; c < LENGTHOF( initializedRooms[r]->creeps ); c++ )
   {
      initializedRooms[r]->creeps[c] = NULL;
   }
   return true;
}