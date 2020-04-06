#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include "Creep.h"
#include "../Tools.h"
namespace core::game
{
   void Creep::setTarget( const name_t& target )
   {
      this->val["memory"].set<std::string,name_t>("target", target);
      this->target = target;
   }
   void Creep::setAction( const ActionType& action, const bool resetActionStatus )
   {
      this->val["memory"].set<std::string,int>("action", action);
      this->action = action;
      if( resetActionStatus )
      {
         this->setActionStatus( ACTION_STATUS_INIT );
      }
   }
   void Creep::setAction( const ActionType& action )
   {
      this->setAction( action, true );
   }
   void Creep::setActionStatus( const actionStatus_t& status )
   {
      this->val["memory"].set<std::string,int>("actionStatus", status);
      this->actionStatus = status;
   }
   status_t Creep::say( const std::string& msg )
   {
      return this->val.call<int>( "say", msg );
   }
   status_t Creep::moveTo( const Position& pos )
   {
      return this->val.call<int>( "moveTo", pos.x, pos.y );
   }
}