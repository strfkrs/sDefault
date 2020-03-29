#pragma once
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#include "Loggable.h"
#include "Game.h"

namespace core
{
   namespace api
   {
      typedef std::vector<emscripten::val> valVector_t;
      typedef std::map<std::string,emscripten::val> valMap_t;
      typedef emscripten::val val_t;

      class Api : log::Loggable
      {
         private:
            Api() = delete;
         public:
            static void loop();
         private:
            static void parseInitGame( game::Game& game, const valMap_t& creeps, const valMap_t& spawns, const valMap_t& rooms );
            static void dumpStatistics( const val_t& cpu, const std::string& msg );
         public:
            std::ostream& toString( std::ostream & os ) override { return os << "[ Api ]"; };
      };
      EMSCRIPTEN_BINDINGS(loop) {
         emscripten::function( "loop", &Api::loop );
      }
   }
}