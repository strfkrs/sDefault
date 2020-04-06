#pragma once
#include "../../api/Api.h"
#include "../../Tools.h"
#include "Action.h"
#include "../Creep.h"
namespace core::game
{
   class ActionIdle : public Action
   {
      public:
         ActionIdle() : Action( "ActionIdle" ) {};
      private:
         ActionIdle(const ActionIdle&) = delete;
         void operator=(const ActionIdle&) = delete;
      public:
         virtual status_t run( Creep& creep );
   };

   status_t ActionIdle::run( Creep& creep )
   {
      std::cout << this << creep << std::endl;
      if ( getRand( 5 ) == 0 )
      {
         return creep.say( creep.name );
      }
      return STATUS_OK;
   }

}