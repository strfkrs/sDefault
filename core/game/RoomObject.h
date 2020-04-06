#pragma once
#include "../Type.h"
#include "Position.h"
#include "Storable.h"
#include "../Loggable.h"

namespace core::game
{
   class RoomObject : public Storable, public log::Loggable
   {
      public:
         const api::val_t val;
         const id_t id;
         const Room* room;
         const RoomObjectType type;
         const Position pos;
      private:
      public:
         RoomObject( const api::val_t& _val,
                     const id_t& _id,
                     const Room* _room,
                     const RoomObjectType& _type,
                     const Position _pos,
                     const Storable& storage )
                   : Storable( storage ),
                     val(_val),
                     id(_id),
                     room(_room),
                     type(_type),
                     pos(_pos) { std::cout << this << " created" << std::endl; };
      public:
         std::ostream& toString( std::ostream & os ) override
         {
            return os << Loggable::padding( "RoomObject", 12 )
                      << "[ id: " << this->id
                      << " ][ type: " << this->type
                      << " ]"
                      << (Position&)(this->pos);
         };
   };
   typedef std::map<std::string, RoomObject> roomObjectList_t;
}