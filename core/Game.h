#pragma once
#include <iostream>
#include <map>
#include "Loggable.h"
#include "Creep.h"
#include "Room.h"
#include "Structure.h"

namespace core
{
   namespace game
   {

      class Game : public log::Loggable
      {
         public:
            roomList_t rooms;
         private:
            Game(){};
         public:
            static Game& getInstance()
            {
               static Game instance;
               return instance;
            }
         private:
            Game(Game const&) = delete;
            void operator=(Game const&) = delete;

         public:
            std::ostream& toString( std::ostream & os ) override { return os << "[ Game ]"; };
      };
   }
}