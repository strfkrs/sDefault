Room.prototype.removeCreep = function(creep) {
    return this.removeCreepByName(creep.name, creep.role);
}