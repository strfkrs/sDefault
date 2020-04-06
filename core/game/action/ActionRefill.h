#pragma once
#include "../../api/Api.h"
#include "../../Tools.h"
#include "../Creep.h"
#include "Action.h"
namespace core::game
{
   class ActionRefill : public Action
   {
      public:
         ActionRefill() : Action( "ActionRefill" ) {};
      private:
         ActionRefill(const ActionRefill&) = delete;
         void operator=(const ActionRefill&) = delete;
      public:
         virtual status_t run( Creep& creep );
   };

   status_t ActionRefill::run( Creep& creep )
   {
      std::cout << this << creep << std::endl;
      if ( getRand( 5 ) == 0 )
      {
         return creep.say( "refill" );
      }
      return STATUS_OK;
   }
}