#pragma once
#include "types.h"
#include "room.h"
#include "creep.h"
#include "spawn.h"
#define MAX_ORDERS 20
#define ORDER_MAX_BYTES 10


typedef enum ORDER_TYPE {
   ORDER_TYPE_SPAWN_CREEP,
   ORDER_TYPE_ADD_ACTION
} ORDER_TYPE;

typedef struct Order Order;

typedef struct Order
{
   bool_t consumed;
   ORDER_TYPE type;
   void * sourceEntitiy;
   void * targetEntity;
   byte_t bytes[ORDER_MAX_BYTES];
} Order;

static Order core_orders[MAX_ORDERS];
static Order * orders[MAX_ORDERS];


extern bool_t cleanupOrders();
extern index_t createOrders();
extern index_t getWaitingOrdersCount();
extern byte_t * getNextOrderByteIdx();