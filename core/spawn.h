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

extern bool_t initSpawn( Spawn * spawn, Room * room, bool_t working );
extern bool_t cleanupSpawns();