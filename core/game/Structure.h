#pragma once
#include <string>
#include <map>
#include "../Loggable.h"
#include "../Type.h"
#include "../Tools.h"
#include "../api/ApiType.h"
#include "Storable.h"
#include "GameType.h"
#include "Position.h"

namespace core::game
{
   class Structure : public Storable, public log::Loggable
   {
      public:
         const api::val_t val;
         const name_t name;
         const health_t maxHealth;
         health_t health;
         const Room* room;
         const Position pos;
         const StructureType type;
         const bool my;
         bool isWorking;
      public:
         Structure( const api::val_t& _val,
                     const name_t& _name,
                     const health_t _health,
                     const health_t _maxHealth,
                     const Room* _room,
                     const Position& _pos,
                     const StructureType& _type,
                     const bool& _isWorking,
                     const bool& _my,
                     const Storable& storage )
                  : Storable( storage ),
                     val(_val),
                     room(_room),
                     pos(_pos),
                     health(_health),
                     maxHealth(_maxHealth),
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
                        << " ][ my: " << ((this->my) ? 1 : 0)
                        << " ]" << (Position&)(this->pos);
            return ((Storable*) this)->toString( os );

         };
   };
   typedef std::map<std::string, Structure> structureList_t;
}