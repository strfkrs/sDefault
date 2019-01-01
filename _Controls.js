const l = require("logger");
module.exports = {
    _print: function(p1, p2) {

        l.controls((p1) ? p1 : "", (p2) ? p2 : "");
    },
    _printLines: function(text) {

        const lines = (`\n\n${text}\n\n`).split('\n');

        for (var li = 0; li < lines.length; li++) {
            const line = lines[li];
            if (line.includes('\t')) {
                const parts = line.split('\t');
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
        return this._printLines( "addAggressivePlayer"," name: "+name);
    },
    clearRoomMemory: function() {
        console.log("clearRoomMemory",undefined,"","");
        for (var r in Game.rooms) {
            const room = Game.rooms[r];
            room.memory.creepNames = undefined;
        }
        return this._printLines("clearRoomMemory");
    },
    autoConstructRoad: function() {
        return this.autoConstruct() && (Game.constructionSites || Game.constructionSites.length < 20);
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
    },
    toString: function() {

        const aggressivePlayers = Memory.aggressivePlayers;

        return this._printLines(    
            "CONTROLS"+
            "\n"+
            "\naggressivePlayers:\t"+(aggressivePlayers ? aggressivePlayers.length : 0)+
            "\nautoConstruct:\t"+this.autoConstruct()
        );

    },
    help: function() {
        return this._printLines(    "functions\n"+
                                    "     Controls.clearRoomMemory\n"+
                                    "     Controls.autoConstruct(state)"+
                                    "           state: undefined/false/true (if undefined, do not touch the memory)\n"+
                                    "           returns the current state");
    }
}