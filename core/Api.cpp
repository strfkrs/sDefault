#include <cmath>
#include <iostream>
#include <iomanip>

#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

#include "Api.h"
#include "Game.h"
#include "ApiParser.h"
#include "ApiStatistics.h"

namespace
{
   void dumpStatistics( const core::api::val_t& cpu, const std::string& msg )
   {
      using namespace core::api;
      const val_t heapStatistics = cpu.call<val_t>("getHeapStatistics");
      const unsigned short totalHeap = std::round( heapStatistics["used_heap_size"].as<double>()
                                                   / heapStatistics["total_heap_size"].as<double>() * 100 );
      const unsigned short maxHeap = std::round( heapStatistics["used_heap_size"].as<double>()
                                                / heapStatistics["heap_size_limit"].as<double>() * 100 );
      const float usedCpu = cpu.call<float>("getUsed");
      std::cout << "----------------------------------------------- " << msg << ":\n"
                  << " used heap size [" << totalHeap << "%] total [" << maxHeap << "%]" << "\n"
                  << "----------------------------------------------- " << std::endl;
   }
}

namespace core
{
   namespace api
   {
      std::string parseBodyPartsFromCore( const game::creepBody_t& parts )
      {
         std::string out;
         for ( const auto& p: parts )
         {
            out += ( ( out.size() > 0 ) ? ";" : "" )
                   + game::creepBodyPartMap.find(p)->second;
         }
         return std::move( out );
      }


      bool Api::initGame( game::Game& game )
      {
         using namespace parser;
         const valMap_t rooms = getMap( gameVal["rooms"], this->objectVal );
         const valMap_t creeps = getMap( gameVal["creeps"], this->objectVal );
         const valMap_t structures = getMap( gameVal["structures"], this->objectVal );


         ApiParser::parseInitRooms( game.rooms, rooms );

         for( auto& r : game.rooms )
         {
            ApiParser::parseInitCreeps( &(r.second), r.second.creeps, creeps );
            ApiParser::parseInitStructures( &(r.second), r.second.structures, structures );
         }

         return true;
      }

      status_t Api::spawnCreep( const game::Structure& spawn,
                                const game::name_t& name,
                                const game::Role role,
                                const game::creepBody_t& body )
      {
         using namespace emscripten;
         return spawn.val.call<int>( "spawnCreep", parseBodyPartsFromCore( body ), name, (int)role );
      }

      cpuTime_t Api::getCpuTime()
      {
         return this->cpu.call<cpuTime_t>("getUsed");
      }
   }
}