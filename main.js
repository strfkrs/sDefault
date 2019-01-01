require("__globals");


require("_String.padding");
require("_Spawn.autoSpawn");

require("_Creep.actions");
require("_Creep.focus");
require("_Creep.home");
require("_Creep.job");
require("_Creep.moveTo");
require("_Creep.role");
require("_Flag.surrounds");
require("_Objects.focussedBy");
require("_Room.clean");
require("_Room.creeps");
require("_Room.flags");
require("_Room.sources");
require("_Room.structures");
require("_Room.towers");
require("_Source.maxWorkers");
require("_Source.memory");
require("_Spawn.autoSpawn");
require("_Tower.repair");
require("_Tower.attack");

var l = require("logger");
var cleanup = require("cleanup");

global.CONTROLS = require("_Controls");


global.DEBUG = true;

module.exports.loop = function() {
    
    cleanup();

    l.og("Creeps",{name:""},"","");
    for (var c in Game.creeps) {
        let creep = Game.creeps[c];
        ROLES[creep.role].run(creep);
    }

    l.og("Spawns",{name:""},"","");
    for (var s in Game.spawns) {
        let spawn = Game.spawns[s];
        spawn.autoSpawn();
    }

    l.og("Rooms",{name:""},"","");
    for (var r in Game.rooms) {
        let room = Game.rooms[r];
        let msg =   "Creeps : "+room.creeps.length+
                    " Structures: "+room.structures.length+
                    " Towers: "+room.towers.length;
        l.og("",{name:""},"",msg);

        l.og("Towers",{name:""},"","");
        
        for (var t in room.towers) {
            let tower = room.towers[t];
            l.og("",{name:tower.id},"","");
            tower.attack() || tower.repair();
        }
    }

    /*
    l.og(" Rooms ",{name:""},"","");
    for (var r in Game.rooms) {
        let room = Game.rooms[r];


        l.og(" Sources ",{name:""},"","");
        for (var sr in room.sources) {
            let source = room.sources[sr];
            l.og("",{name:source.id},"","maxWorkers: "+source.maxWorkers);
        }
    }*/

    l.status();
}