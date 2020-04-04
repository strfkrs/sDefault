#pragma once
#include <string>
#include <map>
#include "Loggable.h"
#include "Storable.h"
#include "Type.h"
#include "Tools.h"
#include "ApiType.h"

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
            const api::val_t val;
            const name_t name;
            const Room* room;
            const StructureType type;
            const bool my;
            bool isWorking;
         public:
            Structure( const api::val_t& _val,
                       const name_t& _name,
                       const Room* _room,
                       const StructureType& _type,
                       const bool& _isWorking,
                       const bool& _my,
                       const Storable& storage )
                     : Storable( storage ),
                       val(_val),
                       room(_room),
                       name(_name),
                       type(_type),
                       my(_my),
                       isWorking(_isWorking) { std::cout << (Structure*) this << " created " << std::endl; };
         public:
            std::ostream& toString( std::ostream & os ) override
            {
               os        << Loggable::padding( "Structure", 12 )
                         << "[ name: " << this->name
                         << " ][ type: " << this->type
                         << " ][ isWorking: " << ((this->isWorking) ? 1 : 0)
                         << " ][ my: " << ((this->my) ? 1 : 0) << " ]";
               return ((Storable*) this)->toString( os );

            };
      };
      typedef std::map<std::string, Structure> structureList_t;
      typedef std::map<std::string&, Structure&> structureRefList_t;
   }
}