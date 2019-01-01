module.exports = {
    name: "pickupResources",
    run: function(creep) {
        if(creep.carry.energy < creep.carryCapacity) {
            var targets = creep.room.find(FIND_DROPPED_RESOURCES);
            if(targets.length) {
                let target = targets[0];
                creep.focus = target;
                creep.moveTo(target, {visualizePathStyle: {stroke: '#44ffff'}});
                creep.pickup(target);
                return true;
            }
        }
        return false;
    }
}