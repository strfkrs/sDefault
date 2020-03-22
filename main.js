const Core = require("CoreApi");
const Job = require("Job");

require("_Creep");
require("_Room");

const core = new Core();
console.log( `memory size ${ core.heap.length }` );

module.exports.loop = function () {
   console.log("StartLoop");
   const start = core.init();
   while ( ! core.isInitialized() );
   let creepCounter = 0;
   let spawnCounter = 0;
   let roomCounter = 0;
   for ( let character = "", c = 0; (character = String.fromCharCode( core.heap[start + c] )) != "\0"; c++ )
   {
      core.log( character );
   }

   for ( const r in Game.rooms )
   {
      let room = Game.rooms[r];
      core.initRoom( roomCounter );

      for ( const c in room.creeps )
      {
         let creep = room.creeps[c];
         core.initCreep( creepCounter, roomCounter, creep.role, creep.job );

         // init actions

         creepCounter++;
      }
      for ( const s in room.spawns )
      {
         let spawn = room.spawns[s];
         core.initSpawn( spawnCounter, roomCounter, ( spawn.spawning ) ? 1 : 0 );

         spawnCounter++;
      }

      roomCounter++;
   }

   const numOrders = core.createOrders();

   //while ( core.getWaitingOrdersCount() > 0 )
   for ( let c = 0; c < numOrders; c++)
   {
      const idx = core.getNextOrderByteIdx();
   }
}