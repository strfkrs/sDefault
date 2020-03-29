#pragma once
#include "Loggable.h"

namespace core
{
   namespace game
   {
      class Structure : public log::Loggable
      {
         public:
            Structure(){};
            std::ostream& toString( std::ostream & os ) override { return os << "[ Structure ]"; };
      };
   }
}