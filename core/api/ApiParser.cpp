#include <iostream>
#include <iomanip>
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#include "ApiParser.h"
#include "../game/Game.h"
#include "../game/Storable.h"
#include "../game/Creep.h"
#include "../game/Room.h"
#include "../game/Structure.h"
#include "../Type.h"

namespace core::api::parser
{
   using namespace emscripten;

   bool isNull( const val_t& obj, const std::string& key )
   {
      return obj[key].isNull();
   }

   val_t getValue( const char * name )
   {
      return val::global(name);
   }

   val_t getValue( const std::string& name )
   {
      return val::global(name.c_str());
   }

   template<class T>
   val_t getConst( T&& name )
   {
      return val::global( std::forward<T>( name ));
   }

   valVector_t getVector( const val_t& valArray )
   {
         const unsigned short max = valArray["length"].as<unsigned short>();
         valVector_t vec;
         vec.reserve(max);

         for( unsigned short c = 0; c < max; c++)
         {
            vec.push_back( valArray[c] );
         }

      return vec;
   }
   valMap_t getMap( const val& ele, const val& global ) {
      val keys = global.call<val>("keys", ele );
      const unsigned short max = keys["length"].as<unsigned short>();
      valMap_t map;

      for(int i = 0; i < max; ++i) {
         const auto& key = keys[i].as<std::string>();
         map.emplace_hint(map.end(), key, ele[key]);
      }

      return map;
   }
   void ApiParser::parseInitRooms( core::game::roomList_t& roomList, const core::api::valMap_t& rooms )
   {
      using namespace core;
      using namespace core::game;
      using namespace core::api;

      for( auto r = rooms.begin(); r != rooms.end(); r++ )
      {
         Room room = Room( r->second,
                           (const name_t) r->first,
                           r->second["energyAvailable"].as<int>(),
                           r->second["energyCapacityAvailable"].as<int>() );
         roomList.insert({ r->first, std::move( room ) });
      }
   }
   void ApiParser::parseInitCreeps( core::game::Room* room,
                                    core::game::creepList_t& list,
                                    const core::api::valMap_t& creeps )
   {
      using namespace core::game;
      using namespace core::api;

      for ( auto c = creeps.begin(); c != creeps.end(); c++ )
      {
         Creep creep = Creep( c->second,
                              (const name_t) c->first,
                              room,
                              (RoleType)c->second["role"].as<int>(),
                              (ActionType)c->second["action"].as<int>(),
                              (processStatus_t)c->second["processStatus"].as<int>(),
                              c->second["my"].as<bool>() );
         list.insert({ c->first, creep });
      }
   }
   void ApiParser::parseInitStructures( core::game::Room* room,
                             core::game::structureList_t& list,
                             const core::api::valMap_t& structures )
   {
      using namespace core::api;
      using namespace core::game;

      for ( auto s = structures.begin(); s != structures.end(); s++ )
      {
         const StructureType coreTypeID = (StructureType) s->second["coreTypeID"].as<int>();
         const name_t name = (const name_t) s->first;
         const name_t roomName = (const name_t) s->second["room"]["name"].as<std::string>();
         const val_t store = s->second["store"];
         const bool my = s->second["my"].as<bool>();

         name_t key;
         bool isWorking;
         Storable storage = getEmptyStorageRef();


         if ( coreTypeID == STRUCTURE_SPAWN )
         {
            const resourceQuantity_t energy = (const resourceQuantity_t) store["energy"].as<int>();
            const resourceQuantity_t free = store.call<int>( "getCapacity", getResourceJsType( RESOURCE_ENERGY ) );
            key = s->first;
            isWorking = s->second["spawning"].as<bool>();
            storage = std::move( Storable( true, free, {{ RESOURCE_ENERGY, energy }} ) );


            list.insert({ s->first,
                                   Structure( s->second,
                                              name,
                                              room,
                                              coreTypeID,
                                              s->second["spawning"].as<bool>(),
                                              my,
                                              Storable( true, free, {{ RESOURCE_ENERGY, energy }} ) ) });

         }
         else
         {
            list.insert({ s->first, Structure( s->second, name, room, coreTypeID, my, false, getEmptyStorageRef() ) });
         }
      }
   }
}