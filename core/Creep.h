#pragma once
#include "Loggable.h"
#include <string>
#include <map>

namespace core
{
   namespace game
   {
      class Creep : public log::Loggable
      {
         private:
            std::string name;
         public:
            Creep( const std::string& _name ) : name(_name) {};
            std::ostream& toString( std::ostream & os ) override { return os << "[ Creep ][ " << this->name << "]"; };
      };

      typedef std::map<std::string, Creep> creepList_t;
   }
}