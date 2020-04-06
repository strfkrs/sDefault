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
   unsigned short Game::getAmountOfCreepsWithAction( const creepList_t& creepList, const ActionType& action )
   {
      unsigned short amount = 0;
      for( const auto c : creepList )
      {
         if( c.second.getAction() == action )
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
            return (Creep*) &( match->second );
         }
      }
      return NULL;
   }

   std::string Game::parseBodyPartsFromCore( const game::creepBody_t& parts )
   {
      std::string out;
      for ( const auto& p: parts )
      {
         out += ( ( out.size() > 0 ) ? ";" : "" )
               + game::creepBodyPartMap.find(p)->second;
      }
      return std::move( out );
   }

   name_t Game::createCreepName( Game& game )
   {
      std::array<std::string, 6> names = { "j-ck","j-e","j-m","jo-","j-n","j-ff" };
      std::array<const char, 5> replaceChars = { 'a','e','i','o','u' };
      for( unsigned short c = 0; c < 10; c++ )
      {
         name_t name = names.at( getRand( names.size() ) );
         name_t generated = "";
         std::size_t current, previous = 0;
         const char delim = '-';
         current = name.find(delim);
         do
         {
            generated += name.substr( previous, current - previous ) + randChoice( replaceChars );
            previous = current +1;

         } while ( ( current = name.find( delim, previous ) ) != std::string::npos );

         generated += name.substr( previous, current - previous );

         if( game.findCreepByName( generated ) == NULL )
         {
            return std::move( generated );
         }
      }
      return "ERROR";
   }
   creepBody_t Game::createCreepBody( const storageQuantity_t availableEnergy, const creepBody_t strategy )
   {
      storageQuantity_t remainingEnergy = availableEnergy;
      creepBody_t body;
      while( remainingEnergy > 0 )
      {
         for( auto& sb : strategy )
         {
            const storageQuantity_t nextCosts = creepBodyPartCostsMap.find(sb)->second;
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