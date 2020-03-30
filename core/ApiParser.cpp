#include "ApiParser.h"
#include "Game.h"
#include "Storable.h"
#include "Creep.h"
#include "Room.h"
#include "Structure.h"
#include "Type.h"
#include <iostream>
#include <iomanip>
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>


namespace
{
   void parseInitRooms( core::game::roomList_t& roomList, const core::api::valMap_t& rooms )
   {
      using namespace core::game;
      using namespace core::api;

      for( auto r = rooms.begin(); r != rooms.end(); r++ )
      {
         Room room = Room( (const name_t) r->first );
         roomList.insert({ r->first, std::move( room ) });
      }
   }
   void parseInitCreeps( core::game::creepList_t& creeplist, const core::api::valMap_t& creeps )
   {
      using namespace core::game;
      using namespace core::api;

      for ( auto c = creeps.begin(); c != creeps.end(); c++ )
      {
         Creep creep = Creep( (const name_t) c->first );
         creeplist.insert({ c->first, creep });
      }
   }
   void parseInitStructures( core::game::structureList_t& structurelist, const core::api::valMap_t& structures )
   {
      using namespace core::api;
      using namespace core::game;

      for ( auto s = structures.begin(); s != structures.end(); s++ )
      {
         const StructureType coreTypeID = (StructureType) s->second["coreTypeID"].as<int>();
         const name_t name = (const name_t) s->first;
         const val_t store = s->second["store"];
         if ( coreTypeID == STRUCTURE_SPAWN )
         {
            const resourceQuantity_t energy = (const resourceQuantity_t) store["energy"].as<int>();
            const resourceQuantity_t free = store.call<int>( "getCapacity", getResourceJsType( RESOURCE_ENERGY ) );

            structurelist.insert({ s->first,
                                   Structure( name,
                                              coreTypeID,
                                              s->second["spawning"].as<bool>(),
                                              Storable( true, free, {{ RESOURCE_ENERGY, energy }} ) ) });

         }
         else
         {
            structurelist.insert({ s->first, Structure( name, coreTypeID,  false, getNoneStorageRef() ) });
         }
      }
   }
}

namespace core
{
   namespace api
   {
      namespace parser
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


         void ApiParser::parseInitGame( game::Game& game, const val_t& objVal, const val_t& gameVal )
         {
            using namespace game;
            const valMap_t rooms = getMap( gameVal["rooms"], objVal );
            const valMap_t creeps = getMap( gameVal["creeps"], objVal );
            const valMap_t structures = getMap( gameVal["structures"], objVal );

            parseInitRooms( Game::getInstance().rooms, rooms );

            for( auto& r : Game::getInstance().rooms )
            {
               parseInitCreeps( r.second.creeps, creeps );
               parseInitStructures( r.second.structures, structures );
            }
         }
      }
   }
}