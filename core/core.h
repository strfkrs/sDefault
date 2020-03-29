#pragma once
#include <string>
#include <iostream>
#include "Loggable.h"
#include "Game.h"
namespace core
{
   class Core : public log::Loggable
   {
      // singleton
      public:
         static Core& getInstance()
         {
            static Core instance;
            return instance;
         }
      private:
         Core(){}
         Core(Core const&) = delete;
         void operator=(Core const&) = delete;

      // -----------
      public:
         std::ostream& toString( std::ostream & os ) override { return os << "[ core ]"; };
         static void init();

   };
}