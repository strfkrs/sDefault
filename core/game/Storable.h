#pragma once
#include <map>
#include <iostream>
#include "GameType.h"

namespace core::game
{
   typedef enum ResourceType : unsigned char ResourceType;
   typedef short resourceQuantity_t;
   typedef std::map<ResourceType, resourceQuantity_t> storage_t;

   class Storable
   {
      private:
         storage_t content;
         resourceQuantity_t maxQuantity;
         bool singleResourceType;
      public:
         Storable( const bool single,
                     const resourceQuantity_t _maxQuantity ) : singleResourceType(single),
                                                               maxQuantity(_maxQuantity) {};
         Storable( const bool single,
                     const resourceQuantity_t _maxQuantity,
                     const storage_t& _content             ) : singleResourceType(single),
                                                               maxQuantity(_maxQuantity),
                                                               content(_content) {};
      public:
         void operator=( const Storable & e ) {
            this->content = std::move( e.content );
            this->maxQuantity = std::move( e.maxQuantity );
            this->singleResourceType = std::move( e.singleResourceType );
         }
      /*protected:
         Storable( const Storable& e ) = default;*/
      public:
         const resourceQuantity_t getFreeSpace() const;
         const resourceQuantity_t getQuantityStored() const;
         const resourceQuantity_t getQuantityStored( const ResourceType& type ) const;
         const storage_t& getContent() const { return this->content; }
         const bool changeResource( const ResourceType type, const resourceQuantity_t diff );

      public:
         std::ostream& toString( std::ostream & os );
   };

   extern const ResourceType& getResourceCoreType( const std::string& resourceType );
   extern const std::string& getResourceJsType( const ResourceType& resourceType );
   extern const Storable& getEmptyStorageRef();
}