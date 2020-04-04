#pragma once
#include <string>
#include <iostream>
#include "Loggable.h"
#include "Game.h"
#include "Api.h"
namespace core
{
   class Core : public log::Loggable
   {
      public:
         Core(){ std::cout << this << " created" << std::endl; }
      private:
         Core(Core const&) = delete;
         void operator=(Core const&) = delete;
      public:
         std::ostream& toString( std::ostream & os ) override { return os << Loggable::padding( "Core", 12 ); };
         static void loop();
         status_t run( game::Game& game, api::Api& api );
   };
}