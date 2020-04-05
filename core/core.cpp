#include "Core.h"
#include "Type.h"
#include "Tools.h"
#include "Loggable.h"
#include "api/Api.h"
#include "game/Game.h"
#include "game/Room.h"
#include "game/Structure.h"
#include "game/Creep.h"
#include "game/ActionFactory.h"

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
         spawnCreep( room );

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

   core::status_t Core::spawnCreep( core::game::Room& room )
   {
      using namespace core::game;
      using namespace core;
      const auto& creeps = room.creeps;
      status_t status = STATUS_OK;

      if( room.energy == room.maxEnergy && Game::getAmountOfCreepsWithRole( creeps, ROLE_WORKER ) < 3 )
      {
         do
         {
            creepBody_t body;

            auto spawn = find_if( room.structures, [&]( const auto& s ){ return s.second.type == STRUCTURE_SPAWN
                                                                             && s.second.isWorking == false
                                                                             && s.second.my; } );
            status = this->api.spawnCreep( spawn->second,
                                           Game::createCreepName( this->game ),
                                           ROLE_WORKER,
                                           Game::createCreepBody( room.energy, creepBody_t{ BODYPART_MOVE, BODYPART_WORK, BODYPART_CARRY } )
                                         );
         }
         while( status == -3 );
      }
      return status;
   }

   core::status_t Core::evaluateCreepAction( core::game::Creep& creep )
   {
      //Action& action =
      return STATUS_OK;
   }

   status_t Core::executeCreepAction( game::Creep& creep )
   {
      return game::ActionFactory::getAction( creep.getAction() ).run( this->api, creep );
   }
}

namespace emscripten
{
   EMSCRIPTEN_BINDINGS(loop) {
      function( "loop", core::Core::loop );
   }
}
