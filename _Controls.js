var l = require("logger");
module.exports = {
    toString: function() {
        return this._printLines(    "functions\n"+
                                    "     Controls.clearRoomMemory\n"+
                                    "     Controls.autoConstruct(state)"+
                                    "           state: undefined/false/true (if undefined, do not touch the memory)\n"+
                                    "           returns the current state");
    },
    _print: function(p1, p2) {

        let _p2 = (p2) ? p2 : p1;
        let _p1 = (p2) ? p1 : "";


        l.og("CONTROLS",undefined,_p1,_p2);
    },
    _printLines: function(text) {

        let lines = (`\n\n${text}\n\n`).split('\n');

        for (var li = 0; li < lines.length; li++) {
            let line = lines[li];
            if (line.includes('\t')) {
                let parts = line.split('\t');
                this._print(parts[0], parts[1]);
            } else {
                this._print(line);
            }
        }
        return "";
    },
    addAggressivePlayer: function(name) {
        if (!Memory.aggressivePlayers) {
            Memory.aggressivePlayers = [];
        }
        Memory.aggressivePlayers.push (name);
    },
    clearRoomMemory: function() {
        console.log("clearRoomMemory",undefined,"","");
        for (var r in Game.rooms) {
            let room = Game.rooms[r];
            room.memory.creepNames = undefined;
        }
    },
    autoConstruct: function(state) {
        if (state == undefined) {
            if (!global._autoConstruct) {
                if (Memory.autoConstruct) { global._autoConstruct = true }
                else { global._autoConstruct = false }
            }
            return global._autoConstruct;
        }
        global._autoConstruct = state;
        Memory.autoConstruct = state;
        return state;
    }
}