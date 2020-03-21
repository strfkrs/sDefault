#pragma once
#include "room.h"
#include "creep.h"
#include "spawn.h"


static creep creeps[200];
static room rooms[25];
static spawn spawns[75];

static room * initializedRooms[25];
static room ** currentInitializedRoom;