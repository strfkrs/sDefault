#pragma once
#include "ApiType.h"
#include "Loggable.h"
#include "Game.h"
#include "Creep.h"
#include "Type.h"
#include "ApiParser.h"

namespace core
{
   namespace api
   {
      class Api : public log::Loggable
      {
         public:
            const val_t objectVal = val_t::global("Object");
            const val_t gameVal = val_t::global("Game");
            const val_t cpu = gameVal["cpu"];
         public:
            Api() { std::cout << this << " created" << std::endl; }
         private:
            Api(Api const&);
            void operator=(Api const&);
         public:
            bool initGame( game::Game& game );
            status_t spawnCreep( const game::Structure& spawn,
                                 const game::name_t& name,
                                 const game::Role role,
                                 const game::creepBody_t& body );
            cpuTime_t getCpuTime();
         public:
            std::ostream& toString( std::ostream & os ) override { return os << Loggable::padding( "Api", 12 ); };
      };
   }
}