#include <cmath>
#include <iostream>
#include <iomanip>

#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

#include "../game/Game.h"
#include "../game/Creep.h"
#include "Api.h"
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


      bool Api::initGame( game::Game& game )
      {
         std::cout << this << " initializing game " << std::endl;
         using namespace parser;
         const valMap_t rooms = getMap( gameVal["rooms"], this->objectVal );
         const valMap_t creeps = getMap( gameVal["creeps"], this->objectVal );
         const valMap_t structures = getMap( gameVal["structures"], this->objectVal );


         std::cout << this << " parsing rooms " << std::endl;
         ApiParser::parseInitRooms( &game, game.rooms, rooms );

         for( auto& r : game.rooms )
         {
            const valMap_t sources = getMap( r.second.val["sources"], this->objectVal );
            std::cout << this << " parsing creeps " << std::endl;
            ApiParser::parseInitCreeps( &(r.second), r.second.creeps, creeps );
            std::cout << this << " parsing structures " << std::endl;
            ApiParser::parseInitStructures( &(r.second), r.second.structures, structures );
            std::cout << this << " parsing sources " << std::endl;
            ApiParser::parseInitSources( &(r.second), r.second.roomObjects, sources );
         }
         return true;
      }

      cpuTime_t Api::getCpuTime()
      {
         return this->cpu.call<cpuTime_t>("getUsed");
      }
   }
}