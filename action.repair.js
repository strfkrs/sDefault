module.exports = {
    name: "repair",
    _hasCriticalHealth(structure) {
        return structure.hits < structure.hitsMax * 0.8
    },
    _setFocus(creep) {
        creep.focus = undefined;
        
        const targets = creep.room.find(FIND_STRUCTURES, { filter: object => this._hasCriticalHealth(object) });

        if (targets.length) {
            targets.sort((a,b) => a.hits - b.hits);
            creep.focus = targets[0];
        }
    },
    run: function(creep) {
        if (creep.carry.energy > 0) {
            if (!creep.focus) {
                this._setFocus(creep);
            }

            if (creep.focus) {
                if(creep.repair(creep.focus) == ERR_NOT_IN_RANGE) {
                    creep.moveTo(creep.focus, {stroke: '#ffff00'});
                }
                return true;
            }
        }
        return false;
    }
}