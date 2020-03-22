#include "tools.h"

bool_t cleanupPtList( void ** list )
{
   for( index_t c = 0; c < LENGTHOF( list ); c++ )
   {
      list[c] = NULL;
   }
   return true;
}

bool_t addPtToList( void * new, void ** arr )
{
   for( index_t e = 0; e < LENGTHOF(arr); e++ )
   {
      if ( arr[e] == NULL )
      {
         arr[e] = new;
         return true;
      }
   }
   return false;
}