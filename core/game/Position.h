#pragma once
#include "../Type.h"
#include "../Loggable.h"
#include <cmath>
namespace core::game
{
   typedef class Room Room;
   class Position : public log::Loggable
   {
      public:
         const Room* room;
         const roomLength_t x;
         const roomLength_t y;
      public:
         Position( const Room* _room,
                   const roomLength_t _x,
                   const roomLength_t _y )
                 : room(_room),
                   x(_x),
                   y(_y) {};
         friend bool operator==( const Position& a, const Position& b )
         {
            return a.room == b.room && a.x == b.x && a.y == b.y;
         }
      public:
         double getDistance( const Position & target )
         {
            return std::sqrt( ( target.x - this->x ) + ( target.y - this->y ) );
         }
      public:
         std::ostream& toString( std::ostream & os ) override
         {
            return os << "[ x: " << (unsigned short)this->x
                      << " ][ y: " << (unsigned short)this->y
                      << " ][ roomPt: " << this->room << " ]";
         }
   };
}