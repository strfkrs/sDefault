#pragma once
#include <string>
#include <map>
#include "Loggable.h"
#include "Storable.h"
#include "Type.h"

namespace core
{
   namespace game
   {
      enum StructureType : unsigned char
      {
         STRUCTURE_SPAWN,
         STRUCTURE_EXTENSION,
         STRUCTURE_ROAD,
         STRUCTURE_WALL,
         STRUCTURE_RAMPART,
         STRUCTURE_KEEPER_LAIR,
         STRUCTURE_PORTAL,
         STRUCTURE_CONTROLLER,
         STRUCTURE_LINK,
         STRUCTURE_STORAGE,
         STRUCTURE_TOWER,
         STRUCTURE_OBSERVER,
         STRUCTURE_POWER_BANK,
         STRUCTURE_POWER_SPAWN,
         STRUCTURE_EXTRACTOR,
         STRUCTURE_LAB,
         STRUCTURE_TERMINAL,
         STRUCTURE_CONTAINER,
         STRUCTURE_NUKER,
         STRUCTURE_FACTORY,
         STRUCTURE_INVADER_CORE,
      };
      class Structure : public Storable, public log::Loggable
      {
         public:
            const std::string name;
            const StructureType type;
            bool isWorking = false;
         public:
            Structure( const name_t& _name,
                       const StructureType& _type,
                       const bool& _isWorking,
                       const Storable& storage )
                     : Storable( storage ),
                       name(_name),
                       type(_type),
                       isWorking(_isWorking) { std::cout << (Structure*) this << " created " << std::endl; };
         public:
            std::ostream& toString( std::ostream & os ) override
            {
               os        << Loggable::formatClassName( "Structure" )
                         << "[ name: " << this->name
                         << " ][ type: " << this->type
                         << " ][ isWorking: " << ((this->isWorking) ? 1 : 0) << "]";
               return ((Storable*) this)->toString( os );

            };
      };
      typedef std::map<std::string, Structure> structureList_t;
   }
}