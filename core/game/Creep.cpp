#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include "Creep.h"
#include "../Tools.h"
namespace core::game
{
   status_t Creep::say( const std::string& msg )
   {
      return this->val.call<int>( "say", msg );
   }
}