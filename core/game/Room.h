#pragma once
#include <string>
#include <map>
#include <iomanip>
#include "../Loggable.h"
#include "../Type.h"
#include "../api/ApiType.h"
#include "Creep.h"
#include "Structure.h"

namespace core
{
   namespace game
   {
      class Room : public log::Loggable
      {
         public:
            const api::val_t val;
            const name_t name;
            creepList_t creeps;
            structureList_t structures;
            energy_t energy;
            energy_t maxEnergy;
         public:
            Room( const api::val_t _val,
                  const name_t _name,
                  const energy_t _energy,
                  const energy_t _maxEnergy )
                : val(_val),
                  name(_name),
                  energy(_energy),
                  maxEnergy(_maxEnergy) { std::cout << this << " created " << std::endl; };
         public:
            std::ostream& toString( std::ostream & os ) override
            {
               return os << Loggable::padding( "Room", 12 )
                         << "[ name: " << this->name << " ]"
                         << "[ energy: " << this->energy << " ]"
                         << "[ maxEnergy: " << this->maxEnergy << " ]"
                         << "[ structures: " << this->structures.size() << " ]"
                         << "[ creeps: " << this->creeps.size() << " ]";
            };
      };
      typedef std::map<std::string, Room> roomList_t;
      typedef std::map<std::string&, Room&> roomRefList_t;
   }
}