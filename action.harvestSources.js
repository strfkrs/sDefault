var l = require("logger");
module.exports = {
    name: "harvestSources",
    _focusSource(creep) {
        creep.focus = undefined;



        var free = _.filter(creep.room.sources, (s) => s.energy > 0 && s.focussedBy.length < s.maxWorkers)

        l.debug("aHarvest","free "+free.length);

        if (free.length) {
            creep.focus = creep.pos.findClosestByPath(free);
        }
    },
    run: function(creep) {
        if(!creep.focus) {
            if (creep.carry.energy) {
                return false;
            }
            this._focusSource(creep);
        }

        if (creep.focus && _.sum(creep.carry) < creep.carryCapacity) {
            let status = creep.harvest(creep.focus);
            if(status == ERR_NOT_IN_RANGE) {
                creep.moveTo(creep.focus, {visualizePathStyle: {stroke: '#ffaa00'}});
                return true;
            } else if (status == OK) {
                return true;
            }
        }
        return false;
    }
}