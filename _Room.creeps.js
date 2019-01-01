Object.defineProperty(Room.prototype, 'creeps', {
    get: function() {
        if (this._creeps == undefined) {
            
            if (this.memory.creepNames == undefined) {
                this.memory.creepNames = this.find(FIND_MY_CREEPS, (c) => c.home == this).map(f => f.name);
            }
            this._creeps = this.memory.creepNames.map(name => Game.creeps[name]);
        }
        return this._creeps;
    },
    enumerable: false,
    configurable: true
});

Room.prototype.creepsAdd = function(creep) {

    let creeps = this.creeps;
    creeps.push(creep);

    this._creeps = creeps;
    this.memory.creepNames.push(creep.name);
}

Room.prototype.creepsRemoveByName = function(creepName) {

    var creepNames = this.memory.creepNames.slice(0);
    var index = creepNames.indexOf(creepName);

    if (index > -1) {

        creepNames.splice(index, 1);

        this.memory.creepNames = creepNames;
        this._creeps = creepNames.map(name => Game.creeps[name]);
    }
}