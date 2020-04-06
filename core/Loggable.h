#pragma once
#include <string>
#include <functional>
#include <iostream>
#include "Type.h"
namespace core::log
{
   enum LogLevel : unsigned char {
      LOGLEVEL_DEBUG,
      LOGLEVEL_INFO,
      LOGLEVEL_WARN,
      LOGLEVEL_ERROR
   };
   class Loggable
   {
      public:
         virtual os_t& toString(os_t& os) = 0;
         friend os_t& operator<<(os_t& os, Loggable& element);
         friend os_t& operator<<(os_t& os, Loggable* element);
      public:
         static LogLevel logLevel;
         static std::string padding( const char * name, const unsigned char width )
         {
            std::string n(name);
            const char c = ' ';
            const unsigned char len = n.length();
            const unsigned char lpad = ( width / 2 ) - (len / 2) + ( ( len % 2 == 0 ) ? 1 : 0 );
            const unsigned char rpad = ( width / 2 ) - (len / 2);

            n.insert( n.begin(), lpad, c );
            n.append( rpad, c);

            return "[ " + n + " ]";
         }
   };
}