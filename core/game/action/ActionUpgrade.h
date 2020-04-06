#pragma once
#include "../../api/Api.h"
#include "../../Tools.h"
#include "../Creep.h"
#include "Action.h"
namespace core::game
{
   class ActionUpgrade : public Action
   {
      public:
         ActionUpgrade() : Action( "ActionUpgrade" ) {};
      private:
         ActionUpgrade(const ActionUpgrade&) = delete;
         void operator=(const ActionUpgrade&) = delete;
      public:
         virtual status_t run( Creep& creep );
   };

   status_t ActionUpgrade::run( Creep& creep )
   {
      std::cout << this << creep << std::endl;
      if ( getRand( 5 ) == 0 )
      {
         return creep.say( "upgrade" );
      }
      return STATUS_OK;
   }
}