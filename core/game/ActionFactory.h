#pragma once
#include "Action.h"
#include "ActionIdle.h"
#include "Creep.h"
namespace core::game
{
   class ActionFactory
   {
      public:
         static Action& getAction( const ActionType type )
         {
            static ActionIdle actionIdle;
            switch(type)
            {
               case ACTION_IDLE: return actionIdle;
            }
         }
   };
}