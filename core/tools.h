#pragma once
#include "room.h"
#include "creep.h"
#include "spawn.h"
#include "types.h"

#define LENGTHOF(x)  (sizeof(x) / sizeof((x)[0]))
#define LENGTHOF_ROOMS(x)  (sizeof(x) / sizeof(Room))
#define LENGTHOF_CREEPS(x)  (sizeof(x) / sizeof(Creep))
#define LENGTHOF_SPAWNS(x)  (sizeof(x) / sizeof(Spawn))

extern bool_t addPtToList( void * new, void ** arr );
extern bool_t cleanupPtList( void ** list );