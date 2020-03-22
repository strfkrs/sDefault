#include "order.h"
#include "tools.h"
#include "types.h"
#include "coreApi.h"

bool_t cleanupOrders()
{
   return cleanupPtList( (void **) orders );
}

bool_t writeSpawnOrderBytes( Order * order, ROLE role, index_t availableEnergy )
{
   byte_t idx = 0;
   switch ( role )
   {
      case ROLE_WORKER:
         order->bytes[idx++] = ROLE_WORKER;
         order->bytes[idx++] = 2; // WORK
         order->bytes[idx++] = 2; // MOVE
         order->bytes[idx++] = 2; // CARRY
         order->bytes[idx++] = 0; // ATTACK
         order->bytes[idx++] = 0; // RANGED_ATTACK
         order->bytes[idx++] = 0; // HEAL
         order->bytes[idx++] = 0; // TOUGH
         order->bytes[idx++] = 0; // CLAIM
      break;
   }
   order->bytesLength = idx;
   return true;
}

index_t amountOfOrdersWithType( ORDER_TYPE type )
{
   index_t amount = 0;
   for ( index_t c = 0; c < MAX_ORDERS; c++ )
   {
      const Order * order = orders[c];
      if ( order != NULL
        && ! order->consumed
        && order->type == type )
      {
         amount++;
      }
   }
   return amount;
}

bool_t createSpawnCreepOrder( Order * order )
{
   const byte_t maxOrders = 3;
   const index_t amountWorkers = amountOfCreepsWithRole( ROLE_WORKER );
   const index_t amountOrdersToSpawn = maxOrders - amountWorkers - amountOfOrdersWithType( ORDER_TYPE_SPAWN_CREEP );

   if ( amountOrdersToSpawn > 0 )
   {
      order->type = ORDER_TYPE_SPAWN_CREEP;
      writeSpawnOrderBytes( order, ROLE_WORKER, 0 );
   }

   return amountOrdersToSpawn > 0;
}

Order * finishOrder( Order * order )
{
   order->consumed = false;
   return order;
}

index_t createOrders()
{
   cleanupOrders();
   Order * currentOrder = core_orders;
   index_t amountCreated = 0;

   for ( index_t c = 0; c < MAX_ORDERS; c++ )
   {
      if ( createSpawnCreepOrder( currentOrder ) )
      {
         orders[c] = finishOrder ( currentOrder ++ );
         amountCreated++;
         continue;
      }

      break;
   }
   return amountCreated;
}

index_t getWaitingOrdersCount()
{
   index_t waitingCount = 0;
   for( index_t c = 0; c < MAX_ORDERS; c++ )
   {
      if ( orders[c] != NULL && ! orders[c]->consumed )
      {
         waitingCount++;
      }
   }
   return waitingCount;
}

byte_t * getNextOrderByteIdx()
{
   for( index_t c = 0; c < MAX_ORDERS; c++ )
   {
      if ( orders[c] != NULL && ! orders[c]->consumed )
      {
         orders[c]->consumed = true;
         return orders[c]->bytes;
      }
   }
   return NULL;
}