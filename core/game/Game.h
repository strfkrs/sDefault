#pragma once
#include <iostream>
#include <map>
#include "../Loggable.h"
#include "../Tools.h"
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
            Creep *               findCreepByName( const name_t& name );
            static creepBody_t    createCreepBody( const storageQuantity_t availableEnergy, const creepBody_t strategy );
            static name_t         createCreepName( Game& game );
            static std::string    parseBodyPartsFromCore( const game::creepBody_t& parts );
            static unsigned short getAmountOfCreepsWithRole( const game::creepList_t& creepList, const game::RoleType& role );
            static unsigned short getAmountOfCreepsWithAction( const game::creepList_t& creepList, const game::ActionType& action );

            template<class S, class T>
            static status_t transferResource( const ResourceType& resourceType, S& source, T& target );
            template<class T>
            static status_t moveCreep( Creep& creep, T& target );

         public:
            std::ostream& toString( std::ostream & os ) override { return os << Loggable::padding( "Game", 12 ); };
      };

      template<class S, class T>
      status_t Game::transferResource( const ResourceType& resourceType, S& source, T& target )
      {
         if ( instanceof<Creep>(&target) || instanceof<RoomObject>(&source) )
         {
            Creep& creep = (Creep&) target;
            RoomObject& obj = (RoomObject&) source;
            return creep.val.call<int>( "harvest", obj.val );
         }
         return STATUS_ERROR;
      }

      template<typename T>
      status_t Game::moveCreep( Creep& creep, T& target )
      {
         if ( instanceof<Creep>(target) || instanceof<RoomObject>(target) )
         {
            Creep& t = (Creep&) target;
            return creep.moveTo( t.pos );
         }
         return STATUS_ERROR;
      }

      /*template<>
      status_t Game::moveCreep( Creep& creep, RoomObject& target )
      {
         return creep.val.call<int>( "moveTo", target.pos.x, target.pos.y );
      }*/
   }
}