#pragma once
#include "Loggable.h"
#include <string>
#include <map>
#include "ApiType.h"

namespace core
{
   namespace game
   {
      enum Role : unsigned char
      {
         ROLE_WORKER
      };
      enum CreepBodyPart : unsigned char
      {
         BODYPART_MOVE,
         BODYPART_WORK,
         BODYPART_CARRY,
         BODYPART_ATTACK,
         BODYPART_RANGED_ATTACK,
         BODYPART_TOUGH,
         BODYPART_HEAL,
         BODYPART_CLAIM
      };
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
            const Role role;
            const bool my;
         public:
            Creep( const api::val_t& _val,
                   const std::string& _name,
                   const Room* _room,
                   const Role _role,
                   const bool& _my ) : name(_name),
                                        room(_room),
                                        role(_role),
                                        val(_val),
                                        my(_my) { std::cout << this << " created " << std::endl; };
         public:
            std::ostream& toString( std::ostream & os ) override { return os << Loggable::padding( "Creep", 12 )
                                                                             << "[ " << this->name
                                                                             << " ][ role: " << this->role
                                                                             << " ][ my: " << ((this->my) ? 1 : 0) << " ]"; };
      };

      typedef std::map<std::string, Creep> creepList_t;
      typedef std::map<std::string&, Creep&> creepRefList_t;

   }
}