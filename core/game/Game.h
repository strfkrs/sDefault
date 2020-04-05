#pragma once
#include <iostream>
#include <map>
#include "../Loggable.h"
#include "Creep.h"
#include "Room.h"
#include "Structure.h"
#include "GameType.h"

namespace core
{
   namespace game
   {

      class Game : public log::Loggable
      {
         public:
            roomList_t rooms;
         public:
            Game(){ std::cout << this << " created" << std::endl; };
         private:
            Game(Game const&) = delete;
            void operator=(Game const&) = delete;
         public:
            Creep * findCreepByName( const name_t& name );
            static creepBody_t createCreepBody( const energy_t availableEnergy, const creepBody_t strategy );
            static name_t createCreepName( Game& game );
            static unsigned short getAmountOfCreepsWithRole( const game::creepList_t& creepList, const game::RoleType& role );
         public:
            std::ostream& toString( std::ostream & os ) override { return os << Loggable::padding( "Game", 12 ); };
      };
   }
}