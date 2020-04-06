#pragma once
#include "../Creep.h"
#include "../../api/Api.h"
#include "../../Loggable.h"
namespace core::game
{
   class Action : public log::Loggable
   {
      private:
         const std::string name;
      protected:
         Action( const std::string& _name )
               : name(_name) { std::cout << this << " created " << std::endl; };
         //Action(const Action&) = delete;
      private:
         void operator=(const Action&) = delete;
      public:
         virtual status_t run( Creep& creep ) = 0;
      public:
         std::ostream& toString( std::ostream & os ) override { return os << Loggable::padding( this->name.c_str(), 12 ); };
   };
}