#pragma once
#include "Action.h"
#include "../Game.h"
namespace core::game
{
   class ActionHarvest : public Action
   {
      public:
         ActionHarvest() : Action( "ActionHarvest" ) {};
      private:
         ActionHarvest(const ActionHarvest&) = delete;
         void operator=(const ActionHarvest&) = delete;
      public:
         virtual status_t run( Creep& creep );
   };

   status_t ActionHarvest::run( Creep& creep )
   {
      std::cout << this << creep << std::endl;
      Game& game = (Game&)*(creep.room->game);
      Room& room = (Room&) * creep.room;
      status_t reply = STATUS_OK;

      if( creep.getActionStatus() == ACTION_STATUS_INIT )
      {
         const auto match = find_if( room.roomObjects, [&]( const auto& o ){ return o.second.type == ROOM_OBJECT_SOURCE
                                                                                 && o.second.getQuantityStored( RESOURCE_ENERGY ) > 0;
                                                                           } );
         if ( match != room.roomObjects.end() )
         {
            creep.setTarget( match->second.id );
            creep.setActionStatus( ACTION_STATUS_PROCESSING );
         }
         else
         {
            reply = STATUS_ERROR;
         }
      }
      else if ( creep.getActionStatus() == ACTION_STATUS_PROCESSING )
      {
         if( creep.getTarget() == getEmptyStringRef() )
         {
            creep.setActionStatus( ACTION_STATUS_FINISHED );
         }
         if ( creep.getFreeSpace() > 0 )
         {
            const auto match = find_if( room.roomObjects, [&]( const auto& o ){ return o.second.id == creep.getTarget(); });

            if ( match != room.roomObjects.end() )
            {
               reply = Game::transferResource( RESOURCE_ENERGY, match->second, creep );
               if ( reply == STATUS_ERROR_NOT_IN_RANGE )
               {
                  reply = creep.moveTo( (Position&)match->second.pos );
               }
            }
         }
         else
         {
            creep.setActionStatus( ACTION_STATUS_FINISHED );
         }

      }
      return reply;
   }
}