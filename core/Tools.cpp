#include "Tools.h"
namespace core
{
   unsigned short getRand( unsigned short max )
   {
      static unsigned short add = 0;
      std::srand(std::time(nullptr) + (--add));
      return std::rand() % max;
   }
}