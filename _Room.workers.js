const l = require("logger");

Object.defineProperty(Room.prototype, 'workers', {
    get: function() {
        if (this._workers == undefined) {
            
            if (this.memory.workerNames == undefined) {
                this.memory.workerNames = this.creeps.map(f => f.name);
            }
            this._workers = this.memory.workerNames.map(name => Game.creeps[name]);
        }
        return this._workers;
    },
    set: function(newValue) {
        
        this.memory.workerNames = newValue.map(f => f.name);
        this._workers = newValue;
    },
    enumerable: false,
    configurable: true
});