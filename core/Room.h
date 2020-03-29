#pragma once
#include "Loggable.h"
#include "Creep.h"
#include "Structure.h"

namespace core
{
   namespace game
   {
      class Room : public log::Loggable
      {
         private:
            std::map<std::string, Creep> creeps;
            std::map<std::string, Structure> structures;
         public:
            Room();
      };
   }
}