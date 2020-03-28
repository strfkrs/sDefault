#pragma once
#include <string>
#include <functional>
#include <iostream>
namespace core
{
   namespace log
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
            virtual std::ostream& toString(std::ostream& os) = 0;
            friend std::ostream& operator<<(std::ostream& os, Loggable& element);
         public:
            static LogLevel logLevel;
      };
   }
}