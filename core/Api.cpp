#include <cmath>
#include <iostream>
#include <iomanip>

#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

#include "Api.h"
#include "Game.h"
#include "Core.h"
#include "ApiParser.h"
#include "ApiStatistics.h"

namespace
{
   void dumpHeapStatistics( const core::api::val_t& cpu, const std::string& msg )
   {
      using namespace core::api;
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
}

namespace core
{
   namespace api
   {
      void Api::loop()
      {
         using namespace game;
         using namespace emscripten;
         using namespace parser;

        // const val object = val_t::global("Object");
         const val_t objectVal = val_t::global("Object");
         const val_t gameVal = val_t::global("Game");
         const val_t cpu = gameVal["cpu"];


         Core& core = Core::getInstance();
         Game& game = Game::getInstance();
         ApiParser::getInstance().parseInitGame( game, objectVal, gameVal );


         dumpHeapStatistics( cpu, "end");

      }


   }
}