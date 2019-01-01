module.exports = {
    name: "transferEnergyToTowers",
    run: function(creep) {
        if(creep.carry.energy != 0) {
            let targets = creep.room.find(FIND_STRUCTURES, {
                filter: (structure) => {
                    return ( structure.structureType == STRUCTURE_TOWER ) && structure.energy < structure.energyCapacity;
                }
            });

            targets.sort((a,b) => a.energy - b.energy);

            if(targets.length > 0) {
                for (var c = 0; c < targets.length; c++) {
                    if (targets[c].energy < targets[c].energyCapacity) {
                        if( creep.transfer(targets[c], RESOURCE_ENERGY) == ERR_NOT_IN_RANGE) {
                            creep.moveTo(targets[c], {visualizePathStyle: {stroke: '#ffffff'}});
                        }
                        return true;
                    }
                }
            }
        }
        return false;
    }
}