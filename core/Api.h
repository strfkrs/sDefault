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
         public:
            static Api& instance()
            {
               static Api instance;
               return instance;
            }
         private:
            Api(){};
            Api(Api const&) = delete;
            void operator=(Api const&) = delete;
         public:
            static void init();
            static void parseInitGame( game::Game& game );
            static void dumpStatistics( val_t& cpu );
         public:
            std::ostream& toString( std::ostream & os ) override { return os << "[ Api ]"; };
      };

      EMSCRIPTEN_BINDINGS(loop) {
         emscripten::function( "init", &Api::init );
      }

      EMSCRIPTEN_BINDINGS(constant) {
         emscripten::constant( "ROLE_WORKER", (const unsigned char) 1 );
      }
   }
}