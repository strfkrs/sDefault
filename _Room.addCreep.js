const l = require("logger");
Room.prototype.addCreep = function(creep) {

    l.debug("Room.addCreep: "+creep.name);

    let creeps = this.creeps;
    if (!creeps.includes(creep)) {
        creeps.push(creep);
    
        this._creeps = creeps;
        this.memory.creepNames.push(creep.name);
    }

    creeps = this.workers;
    if (!creeps.includes(creep)) {
        creeps.push(creep);
    
        this._workers = creeps;
        this.memory.workerNames.push(creep.name);
    }
}