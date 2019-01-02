require("__globals");


require("_String.padding");
require("_Spawn.autoSpawn");

require("_Creep.actions");
require("_Creep.focus");
require("_Creep.home");
require("_Creep.job");
require("_Creep.moveTo");
require("_Creep.role");
require("_Creep.runActions");
require("_Flag.surrounds");
require("_Objects.focussedBy");
require("_Room.autoConstruct");
require("_Room.creeps");
require("_Room.flags");
require("_Room.maxWorkers");
require("_Room.addCreep");
require("_Room.removeCreep");
require("_Room.removeCreepByName");
require("_Room.sources");
require("_Room.structures");
require("_Room.towers");
require("_Room.workers");
require("_Source.maxWorkers");
require("_Source.memory");
require("_Spawn.autoSpawn");
require("_Tower.autoRepair");
require("_Tower.autoAttack");

const hello = require('hello');
const wasmHello = new WebAssembly.Module(hello);

const imports = {};

// Some predefined environment for Emscripten. See here:
// https://github.com/WebAssembly/tool-conventions/blob/master/DynamicLinking.md
imports.env = {
    memoryBase: 0,
    tableBase: 0,
    memory: new WebAssembly.Memory({ initial: 256 }),
    table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })    
};

const wasmInstance = new WebAssembly.Instance(wasmHello, imports);

var l = require("logger");
var cleanup = require("cleanup");

global.Controls = require("_Controls");

console.log(wasmHello.hello())

module.exports.loop = function() {
    
    cleanup();

    l.init();

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
        let msg =   "Creeps: "+room.creeps.length+
                    " Workers: "+room.workers.length+
                    " Structures: "+room.structures.length+
                    " Towers: "+room.towers.length;
        l.og("",room,"",msg);

        l.og("Towers",{name:""},"","");
        
        for (var t in room.towers) {
            let tower = room.towers[t];
            l.og("",{name:tower.id},"","");
            tower.attack() || tower.repair();
        }
    }
    l.status();
}