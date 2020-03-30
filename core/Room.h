#pragma once
#include <string>
#include <map>
#include <iomanip>
#include "Loggable.h"
#include "Creep.h"
#include "Structure.h"
#include "Type.h"

namespace core
{
   namespace game
   {
      class Room : public log::Loggable
      {
         public:
            const name_t name;
            creepList_t creeps;
            structureList_t structures;
         public:
            Room( const name_t _name )
                : name(_name) { std::cout << this << " created " << std::endl; };
         public:
            std::ostream& toString( std::ostream & os ) override
            {
               return os << Loggable::formatClassName( "Room" )
                         << "[ name: " << this->name << " ]"
                         << "[ structures: " << this->structures.size() << " ]"
                         << "[ creeps: " << this->creeps.size() << " ]";
            };
      };
      typedef std::map<std::string, Room> roomList_t;
   }
}