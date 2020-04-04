#pragma once
#include <map>
#include <iostream>

namespace core
{
   namespace game
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
               this->content = e.content;
               this->maxQuantity = e.maxQuantity;
               this->singleResourceType = e.singleResourceType;
            }
         /*protected:
            Storable( const Storable& e ) = default;*/
         public:
            const storage_t& getContent() const { return this->content; }
            const bool changeResource( const ResourceType type, const resourceQuantity_t diff );

         public:
            std::ostream& toString( std::ostream & os );
      };

      extern const ResourceType& getResourceCoreType( const std::string& resourceType );
      extern const std::string& getResourceJsType( const ResourceType& resourceType );
      extern const Storable& getEmptyStorageRef();

      enum ResourceType : unsigned char
      {
         RESOURCE_ENERGY, RESOURCE_POWER,
         RESOURCE_HYDROGEN, RESOURCE_OXYGEN,RESOURCE_UTRIUM, RESOURCE_LEMERGIUM,RESOURCE_KEANIUM, RESOURCE_ZYNTHIUM,RESOURCE_CATALYST,RESOURCE_GHODIUM,
         RESOURCE_SILICON,RESOURCE_METAL,RESOURCE_BIOMASS,RESOURCE_MIST,
         RESOURCE_HYDROXIDE,RESOURCE_ZYNTHIUM_KEANITE,RESOURCE_UTRIUM_LEMERGITE,
         RESOURCE_UTRIUM_HYDRIDE,RESOURCE_UTRIUM_OXIDE,RESOURCE_KEANIUM_HYDRIDE,RESOURCE_KEANIUM_OXIDE,RESOURCE_LEMERGIUM_HYDRIDE,RESOURCE_LEMERGIUM_OXIDE,RESOURCE_ZYNTHIUM_HYDRIDE,RESOURCE_ZYNTHIUM_OXIDE,RESOURCE_GHODIUM_HYDRIDE,RESOURCE_GHODIUM_OXIDE,
         RESOURCE_UTRIUM_ACID,RESOURCE_UTRIUM_ALKALIDE,RESOURCE_KEANIUM_ACID,RESOURCE_KEANIUM_ALKALIDE,RESOURCE_LEMERGIUM_ACID,RESOURCE_LEMERGIUM_ALKALIDE,RESOURCE_ZYNTHIUM_ACID,RESOURCE_ZYNTHIUM_ALKALIDE,RESOURCE_GHODIUM_ACID,RESOURCE_GHODIUM_ALKALIDE,
         RESOURCE_CATALYZED_UTRIUM_ACID,RESOURCE_CATALYZED_UTRIUM_ALKALIDE,RESOURCE_CATALYZED_KEANIUM_ACID,RESOURCE_CATALYZED_KEANIUM_ALKALIDE,RESOURCE_CATALYZED_LEMERGIUM_ACID,RESOURCE_CATALYZED_LEMERGIUM_ALKALIDE,RESOURCE_CATALYZED_ZYNTHIUM_ACID,RESOURCE_CATALYZED_ZYNTHIUM_ALKALIDE,RESOURCE_CATALYZED_GHODIUM_ACID,RESOURCE_CATALYZED_GHODIUM_ALKALIDE,
         RESOURCE_OPS,
         RESOURCE_UTRIUM_BAR,RESOURCE_LEMERGIUM_BAR,RESOURCE_ZYNTHIUM_BAR,RESOURCE_KEANIUM_BAR,RESOURCE_GHODIUM_MELT,RESOURCE_OXIDANT,RESOURCE_REDUCTANT,RESOURCE_PURIFIER,RESOURCE_BATTERY,
         RESOURCE_COMPOSITE,RESOURCE_CRYSTAL,RESOURCE_LIQUID,
         RESOURCE_WIRE,RESOURCE_SWITCH,RESOURCE_TRANSISTOR,RESOURCE_MICROCHIP,RESOURCE_CIRCUIT,RESOURCE_DEVICE,
         RESOURCE_CELL,RESOURCE_PHLEGM,RESOURCE_TISSUE,RESOURCE_MUSCLE,RESOURCE_ORGANOID,RESOURCE_ORGANISM,
         RESOURCE_ALLOY,RESOURCE_TUBE,RESOURCE_FIXTURES,RESOURCE_FRAME,RESOURCE_HYDRAULICS,RESOURCE_MACHINE,
         RESOURCE_CONDENSATE,RESOURCE_CONCENTRATE,RESOURCE_EXTRACT,RESOURCE_SPIRIT,RESOURCE_EMANATION,RESOURCE_ESSENCE
      };

      const static std::map<ResourceType, std::string> resourceMap
      {
         { RESOURCE_ENERGY, "energy" },
         { RESOURCE_POWER, "power" },

         { RESOURCE_HYDROGEN, "H" },
         { RESOURCE_OXYGEN, "O" },
         { RESOURCE_UTRIUM, "U" },
         { RESOURCE_LEMERGIUM, "L" },
         { RESOURCE_KEANIUM, "K" },
         { RESOURCE_ZYNTHIUM, "Z" },
         { RESOURCE_CATALYST, "X" },
         { RESOURCE_GHODIUM, "G" },

         { RESOURCE_SILICON, "silicon" },
         { RESOURCE_METAL, "metal" },
         { RESOURCE_BIOMASS, "biomass" },
         { RESOURCE_MIST, "mist" },

         { RESOURCE_HYDROXIDE, "OH" },
         { RESOURCE_ZYNTHIUM_KEANITE, "ZK" },
         { RESOURCE_UTRIUM_LEMERGITE, "UL" },

         { RESOURCE_UTRIUM_HYDRIDE, "UH" },
         { RESOURCE_UTRIUM_OXIDE, "UO" },
         { RESOURCE_KEANIUM_HYDRIDE, "KH" },
         { RESOURCE_KEANIUM_OXIDE, "KO" },
         { RESOURCE_LEMERGIUM_HYDRIDE, "LH" },
         { RESOURCE_LEMERGIUM_OXIDE, "LO" },
         { RESOURCE_ZYNTHIUM_HYDRIDE, "ZH" },
         { RESOURCE_ZYNTHIUM_OXIDE, "ZO" },
         { RESOURCE_GHODIUM_HYDRIDE, "GH" },
         { RESOURCE_GHODIUM_OXIDE, "GO" },

         { RESOURCE_UTRIUM_ACID, "UH2O" },
         { RESOURCE_UTRIUM_ALKALIDE, "UHO2" },
         { RESOURCE_KEANIUM_ACID, "KH2O" },
         { RESOURCE_KEANIUM_ALKALIDE, "KHO2" },
         { RESOURCE_LEMERGIUM_ACID, "LH2O" },
         { RESOURCE_LEMERGIUM_ALKALIDE, "LHO2" },
         { RESOURCE_ZYNTHIUM_ACID, "ZH2O" },
         { RESOURCE_ZYNTHIUM_ALKALIDE, "ZHO2" },
         { RESOURCE_GHODIUM_ACID, "GH2O" },
         { RESOURCE_GHODIUM_ALKALIDE, "GHO2" },

         { RESOURCE_CATALYZED_UTRIUM_ACID, "XUH2O" },
         { RESOURCE_CATALYZED_UTRIUM_ALKALIDE, "XUHO2" },
         { RESOURCE_CATALYZED_KEANIUM_ACID, "XKH2O" },
         { RESOURCE_CATALYZED_KEANIUM_ALKALIDE, "XKHO2" },
         { RESOURCE_CATALYZED_LEMERGIUM_ACID, "XLH2O" },
         { RESOURCE_CATALYZED_LEMERGIUM_ALKALIDE, "XLHO2" },
         { RESOURCE_CATALYZED_ZYNTHIUM_ACID, "XZH2O" },
         { RESOURCE_CATALYZED_ZYNTHIUM_ALKALIDE, "XZHO2" },
         { RESOURCE_CATALYZED_GHODIUM_ACID, "XGH2O" },
         { RESOURCE_CATALYZED_GHODIUM_ALKALIDE, "XGHO2" },

         { RESOURCE_OPS, "ops" },

         { RESOURCE_UTRIUM_BAR, "utrium_bar" },
         { RESOURCE_LEMERGIUM_BAR, "lemergium_bar" },
         { RESOURCE_ZYNTHIUM_BAR, "zynthium_bar" },
         { RESOURCE_KEANIUM_BAR, "keanium_bar" },
         { RESOURCE_GHODIUM_MELT, "ghodium_melt" },
         { RESOURCE_OXIDANT, "oxidant" },
         { RESOURCE_REDUCTANT, "reductant" },
         { RESOURCE_PURIFIER, "purifier" },
         { RESOURCE_BATTERY, "battery" },

         { RESOURCE_COMPOSITE, "composite" },
         { RESOURCE_CRYSTAL, "crystal" },
         { RESOURCE_LIQUID, "liquid" },

         { RESOURCE_WIRE, "wire" },
         { RESOURCE_SWITCH, "switch" },
         { RESOURCE_TRANSISTOR, "transistor" },
         { RESOURCE_MICROCHIP, "microchip" },
         { RESOURCE_CIRCUIT, "circuit" },
         { RESOURCE_DEVICE, "device" },

         { RESOURCE_CELL, "cell" },
         { RESOURCE_PHLEGM, "phlegm" },
         { RESOURCE_TISSUE, "tissue" },
         { RESOURCE_MUSCLE, "muscle" },
         { RESOURCE_ORGANOID, "organoid" },
         { RESOURCE_ORGANISM, "organism" },

         { RESOURCE_ALLOY, "alloy" },
         { RESOURCE_TUBE, "tube" },
         { RESOURCE_FIXTURES, "fixtures" },
         { RESOURCE_FRAME, "frame" },
         { RESOURCE_HYDRAULICS, "hydraulics" },
         { RESOURCE_MACHINE, "machine" },

         { RESOURCE_CONDENSATE, "condensate" },
         { RESOURCE_CONCENTRATE, "concentrate" },
         { RESOURCE_EXTRACT, "extract" },
         { RESOURCE_SPIRIT, "spirit" },
         { RESOURCE_EMANATION, "emanation" },
         { RESOURCE_ESSENCE, "essence" }
      };
   }
}