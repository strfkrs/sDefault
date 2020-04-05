#pragma once
#include "Structure.h"
#include "Creep.h"
namespace core::game
{
   class StructureSpawn : public Structure
   {
      public:
         StructureSpawn( const api::val_t& val,
                         const name_t& name,
                         const Room* room,
                         const bool& isWorking,
                         const bool& my,
                         const Storable& storage )
                       : Structure( val, name, room, STRUCTURE_SPAWN, isWorking, my, storage );
      public:
         status_t spawnCreep( name_t& name, RoleType role,  )
   }
}