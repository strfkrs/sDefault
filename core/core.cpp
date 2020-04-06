#include "Core.h"
#include "Type.h"
#include "Tools.h"
#include "Loggable.h"
#include "api/Api.h"
#include "game/Game.h"
#include "game/GameType.h"
#include "game/Room.h"
#include "game/Structure.h"
#include "game/Creep.h"
#include "game/action/ActionFactory.h"
#include "game/StructureSpawn.h"

namespace core
{
   Core::Core()
   {
      this->api.initGame( this->game );
      std::cout << this << " created" << std::endl;
   }

   status_t Core::run()
   {
      using namespace game;
      using namespace api;

      for( auto& r : this->game.rooms )
      {
         Room& room = r.second;

         if( room.energy == room.maxEnergy && Game::getAmountOfCreepsWithRole( room.creeps, ROLE_WORKER ) < 3 )
         {
            const creepBody_t bodyStrat{ BODYPART_MOVE, BODYPART_WORK, BODYPART_CARRY };

            auto structure = find_if( room.structures, [&]( const auto& s ){ return s.second.type == STRUCTURE_SPAWN
                                                                              && s.second.isWorking == false
                                                                              && s.second.my; } );
            if ( structure != room.structures.end() )
            {
               StructureSpawn& spawn = (StructureSpawn&) (structure->second);
               spawn.spawnCreep( Game::createCreepName( this->game ),
                                 ROLE_WORKER,
                                 Game::parseBodyPartsFromCore( Game::createCreepBody( room.energy, bodyStrat ) )
                               );
            }
         }

         for ( auto& c : room.creeps )
         {
            Creep& creep = c.second;
            this->evaluateCreepAction( creep );
            this->executeCreepAction( creep );
         }
      }
      return STATUS_OK;
   }

   void Core::loop()
   {
      Core core;
      core.log( "core initialized" );

      core.log( "core run" );
      core.run();

      core.log( "END" );
      std::cout << '\n';
   }
   void Core::log( const char * msg )
   {
      using namespace core::log;
      std::cout << *this << "[ " << std::fixed << std::setprecision(2) << this->api.getCpuTime()
                << " ]" << Loggable::padding( msg, 20 ) << std::endl;
   }
   status_t Core::evaluateCreepAction( game::Creep& creep )
   {
      using namespace game;
      const creepList_t& roomCreeps = creep.room->creeps;
      const unsigned short creepAmount = roomCreeps.size();
      const unsigned short upgraderAmount = Game::getAmountOfCreepsWithAction( roomCreeps, ACTION_UPGRADE );
      const unsigned short harvesterAmount = Game::getAmountOfCreepsWithAction( roomCreeps, ACTION_HARVEST_ENERGY );
      const unsigned short repairerAmount = Game::getAmountOfCreepsWithAction( roomCreeps, ACTION_REPAIR );
      const unsigned short refillerAmount = Game::getAmountOfCreepsWithAction( roomCreeps, ACTION_REFILL );



      if( creep.role == ROLE_WORKER && creep.getAction() == ACTION_IDLE )
      {
         if( creep.getQuantityStored( RESOURCE_ENERGY ) == 0 )
         {
            creep.setAction( ACTION_HARVEST_ENERGY );
         }
      }
      if ( creep.getAction() == ACTION_HARVEST_ENERGY && creep.getActionStatus() == ACTION_STATUS_FINISHED )
      {
         if( upgraderAmount == 0 )
         {
            creep.setAction( ACTION_UPGRADE );
         }
         else if ( repairerAmount == 0 )
         {
            creep.setAction( ACTION_REPAIR );
         }
         else if ( refillerAmount == 0 )
         {
            creep.setAction( ACTION_REFILL );
         }
      }
      return STATUS_OK;
   }

   status_t Core::executeCreepAction( game::Creep& creep )
   {
      return game::ActionFactory::get( creep.getAction() ).run( creep );
   }
}

namespace emscripten
{
   EMSCRIPTEN_BINDINGS(loop) {
      function( "loop", core::Core::loop );
   }
}
