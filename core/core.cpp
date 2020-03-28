#include "Core.h"
#include "Game.h"
#include <iostream>
namespace core
{
   void Core::init( game::Game& game )
   {
      std::cout << *this << " init" << std::endl;
   }
}