#pragma once
#include <iostream>
#include "Loggable.h"
namespace core
{
   namespace game
   {

      class Game : public log::Loggable
      {
         public:
            int _constructed = 0;
            int _timestamp = 0;
         public:
            static Game& instance()
            {
               static Game instance;
               return instance;
            }
         private:

            Game(){};
            Game(Game const&) = delete;
            void operator=(Game const&) = delete;

         public:
            std::ostream& toString( std::ostream & os ) override { return os << "[ Game ]"; };
      };
   }
}