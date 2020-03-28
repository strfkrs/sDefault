#include <cmath>

#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

#include "Api.h"
#include "Core.h"
#include "Game.h"

namespace emType
{
}

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
   valMap_t getMap( const val& obj) {
      val keys = obj.call<val>("keys", obj);
      const unsigned short max = keys["length"].as<unsigned short>();
      valMap_t map;

      for(int i = 0; i < max; ++i) {
         const auto& key = keys[i].as<std::string>();
         map.emplace_hint(map.end(), key, obj[key]);
      }

      return map;
    }
}

namespace core
{
   namespace api
   {
      void Api::init()
      {
         game::Game& game = game::Game::instance();
         Api::parseInitGame( game );
         core::Core::instance().init( game );
      }

      void Api::dumpStatistics( val_t& cpu )
      {
         const val_t heapStatistics = cpu.call<val_t>("getHeapStatistics");
         std::cout << "-----------------------------------------------\n"
                   << "| used cpu [" << cpu.call<float>("getUsed") << "]"
                   << '\n'
                   << "| heapStatistics used heap size ["
                   << std::round( heapStatistics["used_heap_size"].as<double>() / heapStatistics["total_heap_size"].as<double>() * 100 )
                   << "%] total ["
                   << std::round( heapStatistics["used_heap_size"].as<double>() / heapStatistics["heap_size_limit"].as<double>() * 100 )
                   << "%]"
                   << "\n"
                   << "-----------------------------------------------" << std::endl;
      }

      void Api::parseInitGame( game::Game& game )
      {
         using namespace game;
         using namespace emscripten;

         val gameRoot = val::global("Game");
         val cpu = gameRoot["cpu"];
         std::cout << game << std::endl;
         Api::dumpStatistics( cpu );

         return;
      }
   }
}