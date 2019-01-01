var l = require("logger");
module.exports = {
    name: "transferEnergyToStructures",
    _structureNotFull(structure) {
        return ( structure.structureType == STRUCTURE_EXTENSION ||
            structure.structureType == STRUCTURE_SPAWN ) && structure.energy < structure.energyCapacity;
    },
    _focusStructure(creep) {
        const targets = creep.room.find(FIND_STRUCTURES, {
            filter: (structure) => { return this._structureNotFull(structure) }
        });
        if(targets.length) {
            
            targets.sort((a,b) => a.energy - b.energy);
            creep.focus = targets[0];
        }

    },
    run: function(creep) {
        if(creep.carry.energy != 0) {

            this._focusStructure(creep);
            l.debug("aTransfer","focus "+creep.focus);
            if (creep.focus) {
                if( creep.transfer(creep.focus, RESOURCE_ENERGY) == ERR_NOT_IN_RANGE) {
                    creep.moveTo(creep.focus, {visualizePathStyle: {stroke: '#ffffff'}});
                }
                return true;
            }
        }
        return false;
    }
}