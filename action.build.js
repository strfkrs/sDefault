var l = require("logger");
module.exports = {
    name: "build",
    run: function(creep) {
        if (creep.carry.energy > 0) {
            var target = creep.pos.findClosestByPath(FIND_MY_CONSTRUCTION_SITES);
            if(target) {

                let status = creep.build(target);

                if(status == ERR_NOT_IN_RANGE) {
                    if (creep.memory.building) {
                        
                        // finished a construction
                        creep.memory.building = false;

                        // trigger redefinition of room.structures
                        creep.room.structures = undefined;
                    }
                    creep.moveTo(target, {visualizePathStyle: {stroke: '#ffffff'}});
                    
                } else if (status == OK) {
                    creep.memory.building = true;
                    l.og("",creep,"--->", "construction progress: "+target.progress+" total: "+target.progressTotal);
                }
                return true;
            }
        }
        creep.room.structures = undefined;
        return false;
    }
}