#pragma once
#include "Structure.h"
#include "GameType.h"
namespace core::game
{
   class StructureSpawn : public Structure
   {
      public:
         StructureSpawn( const api::val_t& val,
                         const name_t& name,
                         const health_t health,
                         const health_t maxHealth,
                         const Room* room,
                         const Position& pos,
                         const bool& isWorking,
                         const bool& my,
                         const Storable& storage )
                       : Structure( val, name, health, maxHealth, room, pos, STRUCTURE_SPAWN, isWorking, my, storage ) {};
      public:
         status_t spawnCreep( const name_t& name, const RoleType role, const std::string& body );
   };
}