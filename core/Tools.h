#pragma once
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Type.h"
namespace core
{
   extern unsigned short getRand( unsigned short max );

   template<class K, class V, class UnaryPredicate>
   typename std::map<K,V>::const_iterator find_if( const std::map<K,V>& map, UnaryPredicate p )

   {
      return std::find_if( map.begin(), map.end(), p );
   };
   template<class K, class UnaryPredicate>
   typename std::vector<K>::const_iterator find_if( const std::vector<K>& vector, UnaryPredicate p )

   {
      return std::find_if( vector.begin(), vector.end(), p );
   };

   template<class T, size_t size>
   T randChoice( const std::array<T, size> array )
   {
      return array.at( getRand( array.size() ) );
   }

   template<typename Base, typename T>
   inline bool instanceof(const T&) {
      return std::is_base_of<Base, T>::value;
   }
   template<typename Base, typename T>
   inline bool instanceof(const T*) {
      return std::is_base_of<Base, T>::value;
   }
}