#include "order.h"
#include "tools.h"
#include "types.h"
#include "coreApi.h"

bool_t cleanupOrders()
{
   return cleanupPtList( (void **) orders );
}

Order * finishOrder( Order * order )
{
   order->consumed = false;
   return order;
}



void writeSpawnOrderBytes( Order * order, Spawn * spawn, const ROLE role, const index_t availableEnergy )
{
   byte_t idx = 0;
   switch ( role )
   {
      case ROLE_WORKER:
         order->bytes[idx++] = getSpawnIndex( spawn );
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


const index_t createSpawnCreepOrders( const index_t orderIdx, Room * room )
{
   const index_t amountWorkers = getAmountOfCreepsWithRole( ROLE_WORKER );
   const index_t amountEnergy = 0;
   const index_t amountIdleSpawns = getIdleSpawnCountInRoom( room );
   const index_t amountExistingOrders = amountOfOrdersWithType( ORDER_TYPE_SPAWN_CREEP );

   index_t amountOrdersToSpawn = amountIdleSpawns - amountWorkers - amountExistingOrders;
   index_t currentOrderIdx;

   for ( currentOrderIdx = orderIdx;
            currentOrderIdx < MAX_ORDERS
         && amountOrdersToSpawn > 0;
         currentOrderIdx++, amountOrdersToSpawn-- )
   {
      Order * order = &core_orders[currentOrderIdx];
      writeSpawnOrderBytes( order, NULL, ROLE_WORKER, amountEnergy );

      orders[currentOrderIdx] = finishOrder( order );
   }

   return currentOrderIdx;
}

index_t createOrders()
{
   cleanupOrders();
   index_t currentOrderIdx = 0;

   for ( index_t r = 0; r < MAX_ROOMS; r++ )
   {
      if( getRoomByIndex( r ) != NULL )
      {
         currentOrderIdx = createSpawnCreepOrders( currentOrderIdx, rooms[r] );
      }
   }

   return currentOrderIdx;
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