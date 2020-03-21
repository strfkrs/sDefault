#pragma once
#include "types.h"
#include "room.h"

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

typedef struct spawn spawn;
typedef struct creep creep;
typedef struct room room;

typedef struct creep {
   ROLE role;
   JOB job;
   ACTION actions[10];
   index_t numActions;
   room * room;
} creep;

extern bool_t initCreep( creep * creep, room * room, ROLE role, JOB job );
extern bool_t initCreepAction( creep * creep, ACTION action );
