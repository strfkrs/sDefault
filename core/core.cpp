#include "Core.h"
#include "Api.h"
#include "Game.h"
#include "Room.h"
#include "Structure.h"
#include "Creep.h"
#include "Type.h"
#include "Tools.h"
#include "Loggable.h"

namespace
{
   void printLog( core::api::Api& api, core::Core& core, core::game::Game& game, const char * msg )
   {
      using namespace core::log;
      std::cout << core << "[ " << std::fixed << std::setprecision(2) << api.getCpuTime() << " ]" << Loggable::padding( msg, 10 ) << std::endl;
   }
   unsigned short getAmountOfCreepsWithRole( const core::game::creepList_t& creepList, const core::game::Role& role )
   {
      unsigned short amount = 0;
      for( const auto c : creepList )
      {
         if( c.second.role == role )
         {
            amount++;
         }
      }
      return amount;
   }
   core::status_t spawnCreep( core::game::Game& game, core::game::Room& room, core::api::Api& api )
   {
      using namespace core::game;
      creepBody_t body;

      auto spawn = core::find_if( room.structures, [&]( const auto& s ){ return    s.second.type == STRUCTURE_SPAWN
                                                                                && s.second.isWorking == false
                                                                                && s.second.my; } );
      return api.spawnCreep( spawn->second,
                             Game::createCreepName( game ),
                             ROLE_WORKER,
                             Game::createCreepBody( room.energy, creepBody_t{ BODYPART_MOVE, BODYPART_WORK, BODYPART_CARRY } )
                           );
   }
}

namespace core
{
   status_t Core::run( game::Game& game, api::Api& api )
   {
      using namespace game;
      using namespace api;

      for( auto& r : game.rooms )
      {
         Room& room = r.second;
         const auto& creeps = room.creeps;
         if( room.energy == room.maxEnergy && getAmountOfCreepsWithRole( creeps, ROLE_WORKER ) < 3 )
         {
            spawnCreep( game, room, api );
         }
      }
      return STATUS_OK;
   }

   void Core::loop()
   {
      api::Api api;
      game::Game game;
      Core core;
      printLog( api, core, game, "init game" );
      api.initGame( game );
      printLog( api, core, game, "core run" );
      core.run( game, api );
      printLog( api, core, game, "END" );
      std::cout << '\n';
   }
}

namespace emscripten
{
   EMSCRIPTEN_BINDINGS(loop) {
      function( "loop", core::Core::loop );
   }
}
