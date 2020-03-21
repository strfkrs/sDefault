const Core = require("CoreApi");
const Job = require("Job");

require("_Creep");
require("_Room");

const core = new Core();

module.exports.loop = function () {
   core.log("StartLoop");
   for ( const r in Game.rooms )
   {
      let room = Game.rooms[r];
      core.log( "Room: " + room.name );
      for ( const c in room.creeps )
      {
         let creep = room.creeps[c];
         core.log( "Creep: " + creep.name );
      }
      for ( const s in room.spawns )
      {
         let spawn = room.spawns[s];
         core.log( "Spawn: " + spawn.name );
      }
   }
}