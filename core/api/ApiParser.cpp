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
#include "../game/StructureSpawn.h"
#include "../game/RoomObject.h"
#include "../game/Position.h"
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

   game::Position parsePosition( const val_t val, const game::Room* room )
   {
      return game::Position( room,
                             val["pos"]["x"].as<int>(),
                             val["pos"]["y"].as<int>() );
   }

   game::Storable parseStorable( const val_t& val )
   {
      using namespace game;

      Storable storable( false, val.call<int>("getCapacity") );
      const storageQuantity_t used = val.call<int>("getUsedCapacity");
      storageQuantity_t totalFound = 0;

      if( used == 0 )
      {
         return storable;
      }

      for( const auto r : resourceMap )
      {
         const storageQuantity_t found = val.call<int>( "getUsedCapacity", r.second );

         if( found > 0 )
         {
            storable.changeResource( r.first, found );
         }

         if( ( totalFound += found ) == used )
         {
            break;
         }
      }
      return storable;
   }

   game::Storable parseStorable( const val_t& val, const game::ResourceType& type )
   {
      using namespace game;

      const std::string& jsName = getResourceJsType( type );
      const storageQuantity_t max = val.call<int>( "getCapacity", jsName );
      const storageQuantity_t qty = val.call<int>( "getUsedCapacity", jsName );

      return Storable( true, max, {{ type, qty }} );
   }

   //
   // class ApiParser
   //

   void ApiParser::parseInitRooms( core::game::Game* game,
                                   core::game::roomList_t& roomList,
                                   const core::api::valMap_t& rooms )
   {
      using namespace core;
      using namespace core::game;
      using namespace core::api;

      for( auto r = rooms.begin(); r != rooms.end(); r++ )
      {
         Room room = Room( r->second,
                           (const name_t) r->first,
                           game,
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
                              c->second["hits"].as<int>(),
                              c->second["hitsMax"].as<int>(),
                              room,
                              std::move( parsePosition( c->second, room ) ),
                              (RoleType)c->second["role"].as<int>(),
                              (ActionType)c->second["action"].as<int>(),
                              (actionStatus_t)c->second["actionStatus"].as<int>(),
                              c->second["target"].as<name_t>(),
                              c->second["my"].as<bool>(),
                              std::move( parseStorable( c->second["store"] ) )
                             );
         list.insert({ c->first, creep });
      }
   }
   void ApiParser::parseInitSources( core::game::Room* room,
                                    core::game::roomObjectList_t& list,
                                    const core::api::valMap_t& sources )
   {
      using namespace core::game;
      using namespace core::api;
      for ( auto c = sources.begin(); c != sources.end(); c++ )
      {
         const Storable storage( true,
                                 c->second["energyCapacity"].as<int>(),
                                 {{ RESOURCE_ENERGY, c->second["energy"].as<int>() }}
                               );

         RoomObject source = RoomObject( c->second,
                              (const name_t) c->second["id"].as<name_t>(),
                              room,
                              ROOM_OBJECT_SOURCE,
                              std::move( parsePosition( c->second, room ) ),
                              std::move( storage )
                             );
         list.insert({ c->first, std::move( source ) });
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

         if ( coreTypeID == STRUCTURE_SPAWN )
         {
            key = s->first;
            isWorking = s->second["spawning"].as<bool>();
            StructureSpawn structure( s->second,
                                      name,
                                      s->second["hits"].as<int>(),
                                      s->second["hitsMax"].as<int>(),
                                      room,
                                      std::move( parsePosition( s->second, room ) ),
                                      s->second["spawning"].as<bool>(),
                                      my,
                                      std::move( parseStorable( s->second["store"], RESOURCE_ENERGY ) ) );

            list.insert({ s->first, std::move( structure ) });
         }
         else if ( coreTypeID == STRUCTURE_CONTROLLER )
         {
            Structure structure( s->second,
                                 name,
                                 1,
                                 1,
                                 room,
                                 std::move( parsePosition( s->second, room ) ),
                                 coreTypeID,
                                 my,
                                 false,
                                 getEmptyStorageRef() );

            list.insert({ s->first, std::move( structure ) });
         }
      }
   }
}