#pragma once
#include <array>
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
namespace core
{
   typedef float cpuTime_t;
   typedef std::ostream os_t;

   typedef int status_t;
   const status_t STATUS_ERROR_NOT_IN_RANGE = -9;
   const status_t STATUS_ERROR = -99;
   const status_t STATUS_OK = 0;

   namespace game
   {
      typedef int storageQuantity_t;
      typedef unsigned short actionStatus_t;
      typedef class Game Game;
      typedef class Room Room;
      typedef class Creep Creep;
      typedef class Structure Structure;
      typedef unsigned int health_t;
      typedef std::string id_t;
      typedef std::string name_t;
      typedef std::vector<name_t> nameList_t;
      typedef unsigned char roomLength_t;
      const static roomLength_t ROOM_LENGTH = 50;
   }

   namespace api
   {
      typedef std::vector<emscripten::val> valVector_t;
      typedef std::map<std::string,emscripten::val> valMap_t;
      typedef emscripten::val val_t;
   }

   static std::string getEmptyStringRef()
   {
      const static std::string s = "";
      return s;
   }
}
