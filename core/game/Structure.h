#pragma once
#include <string>
#include <map>
#include "../Loggable.h"
#include "../Type.h"
#include "../Tools.h"
#include "../api/ApiType.h"
#include "Storable.h"
#include "GameType.h"

namespace core::game
{
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