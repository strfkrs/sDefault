#pragma once
#include <string>
#include <iostream>
#include "Loggable.h"
#include "game/Game.h"
#include "api/Api.h"
namespace core
{
   class Core : public log::Loggable
   {
      private:
         game::Game game;
         api::Api api;
      public:
         Core();
      private:
         Core(Core const&) = delete;
         void operator=(Core const&) = delete;
      public:
         std::ostream& toString( std::ostream & os ) override { return os << Loggable::padding( "Core", 12 ); };
         static void loop();
         status_t run();
      private:
         void log( const char * msg );
         status_t evaluateCreepAction( core::game::Creep& creep );
         status_t executeCreepAction( core::game::Creep& creep );
   };
}