#pragma once
#include "ApiType.h"
#include "../Type.h"

namespace core::api
{
   class ApiStatistics
   {
      private:
         const cpuTime_t cpuTime;
      public:
         ApiStatistics( const val_t& _cpu )
                        : cpuTime( _cpu.call<cpuTime_t>("getUsed") ) {};
   };
}