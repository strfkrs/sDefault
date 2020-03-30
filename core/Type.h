#pragma once
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
namespace core
{
   typedef unsigned short energy_t;
   typedef float cpuTime_t;
   typedef std::ostream os_t;

   namespace game
   {
      typedef std::string name_t;
   }

   namespace api
   {
      typedef std::vector<emscripten::val> valVector_t;
      typedef std::map<std::string,emscripten::val> valMap_t;
      typedef emscripten::val val_t;
   }
}

