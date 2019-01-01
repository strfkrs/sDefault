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
    autoConstruct: function(roomName, state) {

        const room = Game.rooms[roomName];

        if (room) {
            
            if (state == undefined) {
                return room.autoConstruct;
            } else {
                room.autoConstruct = state;
            }

            return state;
        }

        this._printLines("Controls.autoConstruct: ERROR, room not found");
    },
    toString: function() {

        const aggressivePlayers = Memory.aggressivePlayers;

        return this._printLines(    
            "CONTROLS\n"+
            "\naggressivePlayers:\t"+(aggressivePlayers ? aggressivePlayers.length : 0)
        );

    },
    _getDebugState() {
        if (this._debugState == undefined) {
            if (Memory.debug == undefined) {
                Memory.debug = false;
            }
            this._debugState = Memory.debug;
        }
        return this._debugState;
    },
    _setDebugState(state) {
        Memory.debug = state;
        this._debugState = state;
        returnstate;
    },
    debug: function(state) {
        if (state == undefined) {
            return this._getDebugState();
        } else {

            this._printLines("Setting debug: "+state);
            return this._setDebugState(!(!state));
        }
    },
    help: function() {
        return this._printLines(    "functions\n"+
                                    "     debug(state)"+
                                    "     clearRoomMemory\n"+
                                    "     autoConstruct(state)"+
                                    "           state: undefined/false/true (if undefined, do not touch the memory)\n"+
                                    "           returns the current state");
    }
}