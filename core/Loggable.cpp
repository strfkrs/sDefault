#include "Loggable.h"
#include <iostream>
namespace core
{
   namespace log
   {
      LogLevel Loggable::logLevel = LOGLEVEL_INFO;

      std::ostream& operator<<( std::ostream& os, Loggable& element )
      {
         return element.toString(os);
      };



   }
}