#pragma once
#include "Game.h"
#include "Creep.h"
#include "Room.h"
#include "Structure.h"
#include "ApiType.h"

namespace core
{
   namespace api
   {
      namespace parser
      {

         extern val_t getValue( const char * name );
         extern val_t getValue( const std::string& name );
         template<class T>
         extern val_t getConst( T&& name );
         extern valVector_t getVector( const val_t& valArray );
         extern valMap_t getMap( const val_t& ele, const val_t& global );

         class ApiParser : log::Loggable
         {
            public:
               static ApiParser& getInstance()
               {
                  static ApiParser instance;
                  return instance;
               }
            private:
               ApiParser(){ std::cout << this << " created" << std::endl; };
            private:
               ApiParser(ApiParser const&) = delete;
               void operator=(ApiParser const&) = delete;
            public:
               std::ostream& toString( std::ostream & os ) override
               {
                  return os << Loggable::padding( "ApiParser", 12 );
               };
               static void parseInitRooms( core::game::roomList_t& roomList,
                                           const core::api::valMap_t& rooms );
               static void parseInitCreeps( core::game::Room* room,
                                            core::game::creepList_t& list,
                                            const core::api::valMap_t& creeps );
               static void parseInitStructures( core::game::Room* room,
                                                core::game::structureList_t& list,
                                                const core::api::valMap_t& structures );
         };

      }
   }
}