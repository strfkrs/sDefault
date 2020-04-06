#pragma once
#include <string>
#include <map>
#include "../Loggable.h"
#include "../api/ApiType.h"
#include "../Type.h"
#include "Storable.h"
#include "GameType.h"
#include "Position.h"

namespace core::game
{
   class Creep : public Storable, public log::Loggable
   {
      public:
         const api::val_t val;
         const name_t name;
         const health_t maxHealth;
         health_t health;
         const Room * room;
         const Position pos;
         const RoleType role;
         const bool my;
      private:
         name_t target;
         ActionType action;
         actionStatus_t actionStatus;
      public:
         Creep( const api::val_t& _val,
                  const std::string& _name,
                  const health_t _health,
                  const health_t _maxHealth,
                  const Room* _room,
                  const Position _pos,
                  const RoleType _role,
                  const ActionType _action,
                  const actionStatus_t _actionStatus,
                  const name_t& _target,
                  const bool& _my,
                  const Storable& storage )
               :  Storable( storage ),
                  val(_val),
                  name(_name),
                  health(_health),
                  maxHealth(_maxHealth),
                  room(_room),
                  pos(_pos),
                  role(_role),
                  action(_action),
                  actionStatus(_actionStatus),
                  target(_target),
                  my(_my) { std::cout << this << " created " << std::endl; };

      public:
         const ActionType     getAction() const { return this->action; }
         void                 setAction( const ActionType& action );
         void                 setAction( const ActionType& action, const bool resetActionStatus );
         const name_t&        getTarget() const { return this->target; }
         void                 setTarget( const name_t& target );
         const actionStatus_t getActionStatus() const { return this->actionStatus; }
         void                 setActionStatus( const actionStatus_t& status );
      public:
         status_t say( const std::string& msg );
         status_t moveTo( const Position& pos );

      public:
         std::ostream& toString( std::ostream & os ) override
         {
            return os << Loggable::padding( "Creep", 12 )
                      << "[ " << this->name
                      << " ][ role: " << this->role
                      << " ][ my: " << ((this->my) ? 1 : 0)
                      << " ][ action: " << this->action
                      << " ][ actionStatus: " << this->actionStatus
                      << " ][ target: " << this->target
                      << " ]" << (Position&)(this->pos);
         };
   };

   typedef std::map<std::string, Creep> creepList_t;
   typedef std::map<std::string&, Creep&> creepRefList_t;

}