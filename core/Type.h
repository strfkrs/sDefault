#pragma once
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
namespace core
{
   typedef short energy_t;
   typedef float cpuTime_t;
   typedef std::ostream os_t;

   typedef int status_t;
   const status_t STATUS_ERROR = 1;
   const status_t STATUS_OK = 0;

   namespace game
   {
      typedef unsigned short processStatus_t;
      typedef class Room Room;
      typedef class Creep Creep;
      typedef class Structure Structure;
      typedef std::string name_t;
      typedef std::vector<name_t> nameList_t;
   }

   namespace api
   {
      typedef std::vector<emscripten::val> valVector_t;
      typedef std::map<std::string,emscripten::val> valMap_t;
      typedef emscripten::val val_t;
   }
}
