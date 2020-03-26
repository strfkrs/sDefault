#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <iostream>
#include "core.h"


namespace core
{
   namespace api
   {
      enum class Role : unsigned char {
         ROLE_WORKER
      };

      int tick()
      {
         std::cout << "huhu" << std::endl;
         return 1;
      }
   }
}

EMSCRIPTEN_BINDINGS(loop) {
   emscripten::function( "tick", &core::api::tick );
}

EMSCRIPTEN_BINDINGS(constant) {
   emscripten::constant( "ROLE_WORKER", (const unsigned char) core::api::Role::ROLE_WORKER );
}