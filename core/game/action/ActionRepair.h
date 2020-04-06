#pragma once
#include "../../api/Api.h"
#include "../../Tools.h"
#include "../Creep.h"
#include "Action.h"
namespace core::game
{
   class ActionRepair : public Action
   {
      public:
         ActionRepair() : Action( "ActionRepair" ) {};
      private:
         ActionRepair(const ActionRepair&) = delete;
         void operator=(const ActionRepair&) = delete;
      public:
         virtual status_t run( Creep& creep );
   };

   status_t ActionRepair::run( Creep& creep )
   {
      std::cout << this << creep << std::endl;
      if ( getRand( 5 ) == 0 )
      {
         return creep.say( "repair" );
      }
      return STATUS_OK;
   }
}