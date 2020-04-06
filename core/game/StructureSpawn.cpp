#include "StructureSpawn.h"
#include "GameType.h"
namespace
{

}
namespace core::game
{
   status_t StructureSpawn::spawnCreep( const name_t& name, const RoleType role, const std::string& body )
   {
      return this->val.call<int>( "spawnCreep", body, name, (int)role );
   }
}