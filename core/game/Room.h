#pragma once
#include <string>
#include <map>
#include <iomanip>
#include "../Loggable.h"
#include "../Type.h"
#include "../api/ApiType.h"
#include "Creep.h"
#include "Structure.h"
#include "RoomObject.h"

namespace core
{
   namespace game
   {
      class Room : public log::Loggable
      {
         public:
            const api::val_t val;
            const name_t name;
            const Game* game;
            creepList_t creeps;
            structureList_t structures;
            roomObjectList_t roomObjects;
            storageQuantity_t energy;
            storageQuantity_t maxEnergy;
         public:
            Room( const api::val_t _val,
                  const name_t _name,
                  const Game* _game,
                  const storageQuantity_t _energy,
                  const storageQuantity_t _maxEnergy )
                : val(_val),
                  name(_name),
                  game(_game),
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