#pragma once
#include "Action.h"
#include "ActionIdle.h"
#include "ActionHarvest.h"
#include "ActionUpgrade.h"
#include "ActionRepair.h"
#include "ActionRefill.h"
#include "../GameType.h"
namespace core::game
{
   class ActionFactory
   {
      public:
         static Action& get( const ActionType type )
         {
            static ActionIdle actionIdle;
            static ActionHarvest actionHarvest;
            static ActionUpgrade actionUpgrade;
            static ActionRepair actionRepair;
            static ActionRefill actionRefill;
            switch(type)
            {
               case ACTION_HARVEST_ENERGY: return actionHarvest;
               case ACTION_UPGRADE: return actionUpgrade;
               case ACTION_REPAIR: return actionRepair;
               case ACTION_REFILL: return actionRefill;
               case ACTION_IDLE: return actionIdle;
               default: return actionIdle;
            }
         }
   };
}