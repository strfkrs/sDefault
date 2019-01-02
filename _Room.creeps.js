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
    enumerable: false,
    configurable: true
});

Room.prototype.creepsAdd = function(creep) {

    let creeps = this.creeps;
    if (!creeps.includes(creep)) {
        creeps.push(creep);
    
        this._creeps = creeps;
        this.memory.creepNames.push(creep.name);


        if (creep.role == ROLE_WORKER) {
            this.workersAdd(creep);
        }
    }

}

Room.prototype.creepsRemoveByName = function(creepName) {

    let names = this.memory.creepNames.slice(0);
    if (names.includes(creepName)) {

        const index = names.indexOf(creepName);
        if (index > -1) {
    
            names.splice(index, 1);
    
            this.memory.creepNames = names;
            this._creeps = names.map(name => Game.creeps[name]);
        }
    }
}