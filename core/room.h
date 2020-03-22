#pragma once
#include "types.h"
#include "creep.h"
#include "spawn.h"
#define MAX_ROOMS 25
#define MAX_SPAWNS_PER_ROOM 4
#define MAX_CREEPS_PER_ROOM 100

typedef struct Creep Creep;
typedef struct Room Room;
typedef struct Spawn Spawn;

typedef struct Room {
   Spawn * spawns[MAX_SPAWNS_PER_ROOM];
   Creep * creeps[MAX_CREEPS_PER_ROOM];
} Room;

static Room core_rooms[MAX_ROOMS];
static Room * rooms[MAX_ROOMS];

extern bool_t addSpawnToRoom( Room * room, Spawn * spawn );
extern bool_t addCreepToRoom( Room * room, Creep * creep );

extern bool_t initRoom( Room * room );
extern bool_t cleanupRooms();