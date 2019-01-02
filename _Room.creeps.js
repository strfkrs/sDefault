const l = require("logger");
Object.defineProperty(Room.prototype, 'creeps', {
    get: function() {
        if (this._creeps == undefined) {
            
            if (this.memory.creepNames == undefined) {
                this.memory.creepNames = this.find(FIND_MY_CREEPS).map(f => f.name);
            }
            this._creeps = this.memory.creepNames.map(name => Game.creeps[name]);
        }
        return this._creeps;
    },
    set: function(newValue) {
        
        this.memory.creepNames = newValue.map(f => f.name);
        this._creeps = newValue;
    },
    enumerable: false,
    configurable: true
});