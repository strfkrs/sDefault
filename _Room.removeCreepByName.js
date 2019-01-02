

Room.prototype.removeCreepByName = function(creep, role) {

    const _name = (role) ? creep : creep.name;
    const _role = (role) ? role : creep.role;


    l.debug("Room.removeCreepByName name: "+_name+" role: "+_role);

    let creepNames = this.memory.creepNames.slice(0);
    if (creepNames.includes(_name)) {

        const index = creepNames.indexOf(_name);
        if (index > -1) {
    
            creepNames.splice(index, 1);
    
            this.memory.creepNames = creepNames;
            this._creeps = creepNames.map(name => Game.creeps[name]);
        }
    }


    let creepNames = this.memory.workerNames.slice(0);
    if (creepNames.includes(_name)) {

        const index = creepNames.indexOf(_name);
        if (index > -1) {
    
            creepNames.splice(index, 1);
    
            this.memory.workerNames = creepNames;
            this._workers = creepNames.map(name => Game.creeps[name]);
        }
    }

}