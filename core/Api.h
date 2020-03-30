#pragma once
#include "ApiType.h"
#include "Loggable.h"
#include "Game.h"

namespace core
{
   namespace api
   {
      class Api : log::Loggable
      {
         private:
            Api() = delete;
         public:
            static void loop();
         public:
            std::ostream& toString( std::ostream & os ) override { return os << "[ Api ]"; };
      };
      EMSCRIPTEN_BINDINGS(loop) {
         emscripten::function( "loop", &Api::loop );
      }
   }
}