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
               ApiParser(){};
            private:
               ApiParser(ApiParser const&) = delete;
               void operator=(ApiParser const&) = delete;
            public:
               std::ostream& toString( std::ostream & os ) override
               {
                  return os << Loggable::formatClassName( "ApiParser" );
               };
            public:
               void parseInitGame( game::Game& game, const val_t& objVal, const val_t& gameVal );
         };

      }
   }
}