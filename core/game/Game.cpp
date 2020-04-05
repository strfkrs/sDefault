#include "Game.h"
#include "../Tools.h"
namespace core::game
{
   unsigned short Game::getAmountOfCreepsWithRole( const creepList_t& creepList, const RoleType& role )
   {
      unsigned short amount = 0;
      for( const auto c : creepList )
      {
         if( c.second.role == role )
         {
            amount++;
         }
      }
      return amount;
   }
   Creep * Game::findCreepByName( const name_t& name )
   {
      for ( auto& r : this->rooms )
      {
         const auto match = core::find_if( r.second.creeps, [&]( const auto& creep ){ return creep.second.name == name; } );
         if ( match != r.second.creeps.end() ){
            return (Creep*)&(match->second);
         }
      }
      return NULL;
   }

   name_t Game::createCreepName( Game& game )
   {
      const std::array<std::string, 6> names = { "j-ck","j-e","j-m","jo-","j-n","j-ff" };
      const std::array<const char, 5> replaceChars = { 'a','e','i','o','u' };
      for( unsigned short c = 0; c < 10; c++ )
      {
         name_t name = names.at( getRand( names.size() ) );
         const size_t found = name.find('-');
         const name_t generated = name.substr(0, found)
                                + randChoice<const char>( replaceChars )
                                + name.substr(found+1, name.size());

         if( game.findCreepByName( generated ) == NULL )
         {
            return std::move( generated );
         }
      }
      return "ERROR";
   }
   creepBody_t Game::createCreepBody( const energy_t availableEnergy, const creepBody_t strategy )
   {
      energy_t remainingEnergy = availableEnergy;
      creepBody_t body;
      while( remainingEnergy > 0 )
      {
         for( auto& sb : strategy )
         {
            const energy_t nextCosts = creepBodyPartCostsMap.find(sb)->second;
            if( remainingEnergy - nextCosts < 0 )
            {
               if ( sb == *( --strategy.end() ) )
               {
                  return body;
               }
               continue;
            }
            remainingEnergy -= nextCosts;
            body.push_back( sb );
         }
      }
      return body;
   }
}