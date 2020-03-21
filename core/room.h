#pragma once
#include "types.h"
#include "creep.h"
#include "spawn.h"

typedef struct spawn spawn;
typedef struct creep creep;
typedef struct room room;

typedef struct room {
   spawn * spawns[4];
   creep * creeps[100];
} room;

extern bool_t initRoom( room * room );