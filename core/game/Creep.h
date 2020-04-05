#pragma once
#include <string>
#include <map>
#include "../Loggable.h"
#include "../api/ApiType.h"
#include "../Type.h"
#include "GameType.h"

namespace core::game
{
   const static std::map<CreepBodyPart,std::string> creepBodyPartMap
   {
      { BODYPART_MOVE, "move" },
      { BODYPART_WORK, "work" },
      { BODYPART_CARRY, "carry" },
      { BODYPART_ATTACK, "attack" },
      { BODYPART_RANGED_ATTACK, "ranged_attack" },
      { BODYPART_TOUGH, "tough" },
      { BODYPART_HEAL, "heal" },
      { BODYPART_CLAIM, "claim" }
   };
   const static std::map<CreepBodyPart,energy_t> creepBodyPartCostsMap
   {
      { BODYPART_MOVE, 50 },
      { BODYPART_WORK, 100 },
      { BODYPART_CARRY, 50 },
      { BODYPART_ATTACK, 80 },
      { BODYPART_RANGED_ATTACK, 150 },
      { BODYPART_TOUGH, 10 },
      { BODYPART_HEAL, 250 },
      { BODYPART_CLAIM, 600 }
   };
   typedef std::vector<CreepBodyPart> creepBody_t;
   class Creep : public log::Loggable
   {
      public:
         const api::val_t val;
         const Room * room;
         const name_t name;
         const RoleType role;
         const bool my;
      private:
         ActionType action;
         processStatus_t processStatus;
      public:
         Creep( const api::val_t& _val,
                  const std::string& _name,
                  const Room* _room,
                  const RoleType _role,
                  const ActionType _action,
                  const processStatus_t _processStatus,
                  const bool& _my ) :  val(_val),
                                       name(_name),
                                       room(_room),
                                       role(_role),
                                       action(_action),
                                       processStatus(_processStatus),
                                       my(_my) { std::cout << this << " created " << std::endl; };

      public:
         ActionType       getAction() { return this->action; }
         processStatus_t  getProcessStatus() { return this->processStatus; }
         void             setAction( const ActionType& action ) { this->action = action; }
         void             setProcessStatus( const processStatus_t& status ) { this->processStatus = status; }
      public:
         status_t say( const std::string& msg );
      public:
         std::ostream& toString( std::ostream & os ) override
         {
            return os << Loggable::padding( "Creep", 12 )
                      << "[ " << this->name
                      << " ][ role: " << this->role
                      << " ][ action: " << this->action
                      << " ][ processStatus: " << this->processStatus
                      << " ][ my: " << ((this->my) ? 1 : 0) << " ]";
         };
   };

   typedef std::map<std::string, Creep> creepList_t;
   typedef std::map<std::string&, Creep&> creepRefList_t;

}