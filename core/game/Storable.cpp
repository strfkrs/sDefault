
#include <iostream>
#include "Storable.h"
#include "../Tools.h"
namespace core::game
{
   std::ostream& Storable::toString( std::ostream & os )
   {
      const auto& content = this->getContent();
      for( auto c = content.begin(); c != content.end(); c++ )
      {
         os << "[ " << resourceMap.find(c->first)->second << ": " << c->second << " ]";
      }
      return os;
   }
   const ResourceType& getResourceCoreType( const std::string& resourceType )
   {
      for( auto t = resourceMap.begin(); t != resourceMap.end(); t++ )
      {
         if( t->second == resourceType )
         {
            return t->first;
         }
      }
      std::cout << " ERROR getResourceCoreType no resource found, [" << resourceType << "]" << std::endl;
      throw " please look correct ";
   }
   const Storable& getEmptyStorageRef()
   {
      static const Storable ref( false, 0 );
      return ref;
   }
   const std::string& getResourceJsType( const ResourceType& resourceType )
   {
      return resourceMap.find(resourceType)->second;
   }
   const bool Storable::changeResource( const ResourceType type, const resourceQuantity_t diff )
   {
      auto begin = this->content.begin();
      if(    begin != this->content.end()
            && ( this->singleResourceType == true && type != begin->first ) )
      {
         return false;
      }
      auto match = this->content.find( type );
      if ( match != this->content.end() )
      {
         match->second += diff;
         return true;
      }
      this->content.insert({ type, diff });
      return true;
   }
   const resourceQuantity_t Storable::getQuantityStored() const
   {
      resourceQuantity_t qty = 0;
      for( const auto r : this->content )
      {
         qty += r.second;
      }
      return qty;
   }

   const resourceQuantity_t Storable::getFreeSpace() const
   {
      return this->maxQuantity - this->getQuantityStored();
   }
   const resourceQuantity_t Storable::getQuantityStored( const ResourceType& type ) const
   {
      const auto match = find_if( this->content, [&]( const auto& r ){ return r.first == type; } );
      return ( match == this->content.end() ) ? 0 : match->second;
   }
}