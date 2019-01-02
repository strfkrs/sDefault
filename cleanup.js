module.exports = function() {
    for(var i in Memory.creeps) {
        if(!Game.creeps[i]) {
            let mem = Memory.creeps[i];

            if (Game.rooms[mem.home]) {
                Game.rooms[mem.home].removeCreepByName(i, mem.role);
            }
            delete Memory.creeps[i];
        }
    }
}