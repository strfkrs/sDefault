#include "Loggable.h"
#include <iostream>
#include "Type.h"
namespace core
{
   namespace log
   {
      LogLevel Loggable::logLevel = LOGLEVEL_INFO;

      os_t& operator<<( os_t& os, Loggable& element )
      {
         return element.toString(os);
      };
      os_t& operator<<( os_t& os, Loggable* element )
      {
         return (*element).toString(os);
      };



   }
}