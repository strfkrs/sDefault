#include <cmath>
#include <iostream>
#include <iomanip>

#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

#include "Api.h"
#include "Game.h"
#include "Core.h"

namespace
{
   using namespace emscripten;
   using valVector_t = std::vector<val>;
   using valMap_t = std::map<std::string,val>;
   using val_t = val;

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

   std::vector<val> getVector( const val_t& valArray )
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
   const float getUsedCpu( const val_t& cpu )
   {
      return cpu.call<float>("getUsed");
   }
}

namespace core
{
   namespace api
   {
      void Api::loop()
      {
         using namespace game;
         using namespace emscripten;

        // const val object = val_t::global("Object");
         const val_t objectVal = val_t::global("Object");
         const val_t gameVal = val_t::global("Game");
         const val_t cpu = gameVal["cpu"];
         const valMap_t creeps = getMap( gameVal["creeps"], objectVal );
         const valMap_t spawns = getMap( gameVal["spawns"], objectVal );
         const valMap_t rooms = getMap( gameVal["rooms"], objectVal );

         const float cpuStart = getUsedCpu( cpu );
         Core& core = Core::getInstance();
         core.init();
         const float cpuInitCore = getUsedCpu( cpu );
         Game& game = Game::getInstance();
         parseInitGame( game, creeps, spawns, rooms );
         const float cpuParseInitGame = getUsedCpu( cpu );

         std::cout << '[' << std::setprecision(5) << cpuStart << "] cpuStart \n["
                   << std::setprecision(5) << cpuInitCore << "] cpuInitCore \n["
                   << std::setprecision(5) << cpuParseInitGame << "] cpuParseInitGame" << std::endl;

         Api::dumpStatistics( cpu, "end");

      }

      void Api::dumpStatistics( const val_t& cpu, const std::string& msg )
      {
         const val_t heapStatistics = cpu.call<val_t>("getHeapStatistics");
         const unsigned short totalHeap = std::round( heapStatistics["used_heap_size"].as<double>()
                                                     / heapStatistics["total_heap_size"].as<double>() * 100 );
         const unsigned short maxHeap = std::round( heapStatistics["used_heap_size"].as<double>()
                                                   / heapStatistics["heap_size_limit"].as<double>() * 100 );
         const float usedCpu = cpu.call<float>("getUsed");
         std::cout << "----------------------------------------------- " << msg << ":\n"
                   << "heapStatistics used heap size [" << totalHeap << "%] total [" << maxHeap << "%]" << "\n"
                   << "----------------------------------------------- " << std::endl;
      }

      void Api::parseInitGame( game::Game& game, const valMap_t& creeps, const valMap_t& spawns, const valMap_t& rooms )
      {
         auto creep = creeps.begin();
         while ( creep != creeps.end() )
         {
            std::cout << "creep " << creep->first << std::endl;
            creep ++;
         }

         auto spawnIter = spawns.begin();
         while ( spawnIter != spawns.end() )
         {
            val spawn = spawnIter->second;
            std::cout << "spawn " << spawnIter->first << spawn.call<int>("isActive") << std::endl;
            spawnIter ++;
         }

         auto room = rooms.begin();
         while ( room != rooms.end() )
         {
            std::cout << "room " << room->first << std::endl;
            room ++;
         }
      }
   }
}