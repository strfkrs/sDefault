#pragma once
#include "types.h"
#include "room.h"
#define MAX_SPAWNS 75


typedef struct Creep Creep;
typedef struct Room Room;
typedef struct Spawn Spawn;

typedef struct Spawn {
   bool_t working;
   Room * room;
} Spawn;

static Spawn core_spawns[MAX_SPAWNS];
static Spawn * spawns[MAX_SPAWNS];

extern bool_t initSpawn( index_t idx, index_t roomIdx, bool_t working );
extern bool_t cleanupSpawns();
extern index_t getSpawnIndex( Spawn * spawn );
extern Spawn * getSpawnByIndex( index_t index );
extern index_t getIdleSpawnCountInRoom( Room * room );