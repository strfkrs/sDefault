#pragma once
#include "types.h"
#include "room.h"
#define MAX_CREEPS 200

typedef enum {
   JOB_IDLE,
   JOB_BUILD,
   JOB_HARVEST,
   JOB_UPGRADE,
   JOB_REFILL_STRUCTURE,
   JOB_REFILL_TOWERS
} JOB;

typedef enum {
   ACTION_IDLE
} ACTION;


typedef enum {
   ROLE_WORKER
} ROLE;

typedef struct Creep Creep;
typedef struct Room Room;
typedef struct Spawn Spawn;

typedef struct Creep {
   ROLE role;
   JOB job;
   ACTION actions[10];
   index_t numActions;
   Room * room;
} Creep;

static Creep core_creeps[MAX_CREEPS];
static Creep * creeps[MAX_CREEPS];

extern bool_t initCreep( index_t idx, index_t roomIdx, ROLE role, JOB job );
extern bool_t initCreepAction( index_t creepIdx, ACTION action );
extern bool_t cleanupCreeps();
extern Creep * getCreepByIndex( index_t idx );
extern index_t getAmountOfCreepsWithRole( ROLE role );
